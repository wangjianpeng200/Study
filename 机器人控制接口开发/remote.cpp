#include <opencv2/opencv.hpp>
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <pthread.h>
#include <unistd.h> // usleep
#include <b64/encode.h>
#include <zmq.hpp>           // ZeroMQ C++ bindings
#include <nlohmann/json.hpp> // JSON 库
#include <chrono>
#include <ctime>
#include "config_loader.h"

using json = nlohmann::json;  //命名

class Robot
{
private:
    
public:
    RobotConfig config;
    Robot()
    {
        // 从JSON文件加载配置
        config = ConfigLoader::loadFromFile("config.json");
        cameras = config.cameras;
        arms = config.arms;
        zmq_config = config.zmq;
    }
};

std::tuple<zmq::context_t, zmq::socket_t, zmq::socket_t>
setup_zmq_sockets(const ZMQConfig &config)
{
    zmq::context_t context(1);

    zmq::socket_t cmd_socket(context, ZMQ_PULL);
    cmd_socket.set(zmq::sockopt::conflate, 1);
    cmd_socket.bind("tcp://" + config.ip + ":" + std::to_string(config.port));

    zmq::socket_t video_socket(context, ZMQ_PUSH);
    video_socket.set(zmq::sockopt::conflate, 1);
    video_socket.bind("tcp://" + config.ip + ":" + std::to_string(config.video_port));

    return {std::move(context), std::move(cmd_socket), std::move(video_socket)};
}

std::string base64_encode(const unsigned char *data, size_t len)
{
    const size_t encoded_size = b64_encoded_size(len);
    std::string result(encoded_size, '\0');
    b64_encode(data, len, result.data(), encoded_size);
    return result;
}

// ================== 基类和实现类 ==================
class Camera
{
public:
    virtual cv::Mat async_read() = 0;
    virtual ~Camera() = default;
};

class OpenCVCamera : public Camera
{
public:
    OpenCVCamera(const std::string &device, int fps, int width, int height, int rotation)
        : cap(device), rotation(rotation)
    {
        if (!cap.isOpened())
        {
            throw std::runtime_error("Failed to open camera: " + device);
        }
        cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
        cap.set(cv::CAP_PROP_FPS, fps);
    }
    cv::Mat async_read() override
    {
        cv::Mat frame, rotated;
        if (cap.read(frame))
        {
            cv::rotate(frame, rotated, static_cast<cv::RotateFlags>(rotation));
            return rotated;
        }
        return cv::Mat(); // 返回空矩阵表示失败
    }

private:
    cv::VideoCapture cap;
    int rotation;
};


// ================== 工厂函数 ==================
std::unordered_map<std::string, std::unique_ptr<Camera>>
make_cameras_from_configs(const std::unordered_map<std::string, ::CameraConfig> &configs)
{
    std::unordered_map<std::string, std::unique_ptr<Camera>> cameras;
    for (const auto &[name, config] : configs)
    {
        // 检查配置类型是否为OpenCV相机
        if (config.type == "opencv")
        {
            try
            {
                cameras[name] = std::make_unique<OpenCVCamera>(
                    config.device,
                    config.fps,
                    config.width,
                    config.height,
                    config.rotation);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Failed to create camera: " << name << " - " << e.what() << std::endl;
            }
        }
        else
        {
            std::cerr << "Unsupported config type for camera: " << name << std::endl;
        }
    }
    return cameras;
}

// ================== 线程参数结构 ==================
struct CameraThreadArgs
{
    std::unordered_map<std::string, std::unique_ptr<Camera>> *cameras;
    std::unordered_map<std::string, std::string> *latest_images_dict;
    pthread_mutex_t *images_lock;
    volatile bool *stop_event;
};

// ================== 图像捕获线程 ==================
void *run_camera_capture(void *args)
{
    auto *thread_args = static_cast<CameraThreadArgs *>(args);
    while (!(*thread_args->stop_event))
    {
        std::unordered_map<std::string, std::string> local_dict;

        for (const auto &[name, cam] : *thread_args->cameras)
        {
            cv::Mat frame = cam->async_read();
            if (frame.empty())
                continue;

            std::vector<uchar> buffer;
            cv::imencode(".jpg", frame, buffer);
            local_dict[name] = base64_encode(buffer.data(), buffer.size());
        }

        pthread_mutex_lock(thread_args->images_lock);
        *thread_args->latest_images_dict = local_dict;
        pthread_mutex_unlock(thread_args->images_lock);

        usleep(10000); // 避免 CPU 占用过高
    }
    return nullptr;
}

// ================== 模拟机械臂控制 ==================
class RoboticArm
{
    public:
    virtual void set_position(int motor_id, int position) = 0;
    virtual json read_positions() = 0;
    virtual ~RoboticArm() = default;
}


class gen72: public RoboticArm
{
public:
    void set_position(int motor_id, int position) override
    {
        std::cout << "[INFO] Setting motor " << motor_id << " to " << position << std::endl;
    }

    json read_positions()  override
    {
        return {0, 0, 0, 0, 0, 0, 0, 0}; // 模拟返回当前角度
    }
};

// ================== 主函数 ==================
int main()
{
    // 1. 加载机器人配置
    RobotConfig robot_config;
    // 2. 创建相机实例
    auto cameras = make_cameras_from_configs(robot_config.cameras);
    // 3. 共享数据初始化
    std::unordered_map<std::string, std::string> latest_images;
    pthread_mutex_t images_lock;
    pthread_mutex_init(&images_lock, nullptr);
    // 4. 线程控制变量
    volatile bool stop_event = false;
    // 5. 线程参数设置
    CameraThreadArgs thread_args = {&cameras,&latest_images,&images_lock,&stop_event};
    // 6. 启动图像捕获线程
    pthread_t capture_thread;
    if (pthread_create(&capture_thread, nullptr, run_camera_capture, &thread_args) != 0)
    {
        std::cerr << "Failed to create thread." << std::endl;
        return 1;
    }

    // 7. ZeroMQ 初始化
    RobotConfig robot_config_full = ConfigLoader::loadFromFile("config.json");
    ZMQConfig zmq_config;
    zmq_config.ip = robot_config_full.zmq.ip;
    zmq_config.port = robot_config_full.zmq.command_port;
    zmq_config.video_port = robot_config_full.zmq.video_port;
    auto [context, cmd_socket, video_socket] = setup_zmq_sockets(zmq_config);
    // 8. 初始化机械臂
    RoboticArm arm;
    const std::vector<std::string> arm_motor_ids = {
        "shoulder_pan", "shoulder_lift", "elbow_flex", "wrist_flex",
        "wrist_roll", "wrist_1", "wrist_2", "gripper"};
    time_t last_cmd_time = time(nullptr);
    std::cout << "LeKiwi robot server started. Waiting for commands..." << std::endl;
    try
    {
        while (true)
        {
            // 处理命令
            while (true)
            {
                zmq::message_t msg;
                if (!cmd_socket.recv(msg, zmq::recv_flags::dontwait))  //等待接收ZMQ消息
                {
                    break; // 无更多消息
                }
                try
                {
                    json data = json::parse(msg.to_string());
                    // 处理机械臂指令
                    if (data.contains("arm_positions"))
                    {
                        auto positions = data["arm_positions"];
                        if (positions.is_array() && positions.size() >= arm_motor_ids.size())
                        {
                            for (size_t i = 0; i < arm_motor_ids.size(); ++i)
                            {
                                arm.set_position(i, positions[i].get<int>());
                                //写入
                            }
                        }
                        else
                        {
                            std::cerr << "[ERROR] Invalid arm_positions: " << data.dump() << std::endl;
                        }
                    }
                    // 处理轮子指令
                    if (data.contains("raw_velocity"))
                    {
                        auto wheel_data = data["raw_velocity"];
                        int left = wheel_data.value("left_wheel", 0);
                        int back = wheel_data.value("back_wheel", 0);
                        int right = wheel_data.value("right_wheel", 0);
                        std::cout << "[INFO] Setting wheels to (" << left << ", " << back << ", " << right << ")" << std::endl;
                        //写入
                        last_cmd_time = time(nullptr);
                    }
                }
                catch (const std::exception &e)   //用于捕获异常
                {
                    std::cerr << "[ERROR] Parsing message failed: " << e.what() << std::endl;
                }
            }

            // 看门狗：无命令则停止机器人
            if (time(nullptr) - last_cmd_time > 0.5)
            {
                std::cout << "[INFO] No command received, stopping robot." << std::endl;
                last_cmd_time = time(nullptr);
            }
            /*json velocity_data = {
                {"left_wheel", left_speed},
                {"back_wheel", back_speed},
                {"right_wheel", right_speed}
            };*/

            // 构建观测数据
            {
                std::unordered_map<std::string, std::string> images_copy;
                pthread_mutex_lock(&images_lock);
                images_copy = latest_images;
                pthread_mutex_unlock(&images_lock);

                json observation = {
                    {"images", images_copy},
                    {"present_speed", {0, 0, 0}},
                    {"follower_arm_state", arm.read_positions()}};

                try
                {
                    video_socket.send(zmq::message_t(observation.dump()), zmq::send_flags::none);
                }
                catch (const zmq::error_t &e)
                {
                    std::cerr << "[ERROR] Failed to send observation: " << e.what() << std::endl;
                }
            }

            usleep(33000); // 控制循环频率约30Hz
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "[ERROR] Runtime error: " << e.what() << std::endl;
    }

    // 清理资源
    stop_event = true;
    pthread_join(capture_thread, nullptr);
    pthread_mutex_destroy(&images_lock);
    context.close();

    return 0;
}