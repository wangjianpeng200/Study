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
#include <ctime>
#include "config_loader.h"
#include "new_factory.h"
#include"lekiwi.h"

struct CameraThreadArgs
{
    std::unordered_map<std::string, std::unique_ptr<Camera>> *cameras;
    std::unordered_map<std::string, std::string> *latest_images_dict;
    pthread_mutex_t *images_lock;
    volatile bool *stop_event;
};



// ================== 工厂函数 ==================  根据配置生产camera的具体实例
std::unordered_map<std::string, std::unique_ptr<Camera>>
make_cameras_from_configs(const std::unordered_map<std::string,CameraConfig> &configs)
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

std::unordered_map<std::string, std::unique_ptr<RoboticArm>>
make_arms_from_configs(const std::unordered_map<std::string, ArmConfig> &configs)
{
    std::unordered_map<std::string, std::unique_ptr<RoboticArm>> arms;
    for (const auto &[name, config] : configs)
    {
        // 检查配置类型是否为RoboticArm
        if (config.type == "gen72")
        {
            try
            {
                arms[name] = std::make_unique<Gen72>(configs);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Failed to create arm: " << name << " - " << e.what() << std::endl;
            }
        }
    }
    return arms;
}

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

// ================== 主函数 ==================
int main()
{
    // 1. 加载机器人配置
    RobotConfig robot_config;
    robot_config = ConfigLoader::loadFromFile("config.json");  //robot_config 中有所有的机器人配置信息,由映射组成
    // 2. 创建相机实例
    auto cameras = make_cameras_from_configs(robot_config.cameras);  //实例化机器人和相机实例
    auto arms=make_arms_from_configs(robot_config.arms);
    // 3. 共享数据初始化
    std::unordered_map<std::string, std::string> latest_images;
    pthread_mutex_t images_lock
    pthread_mutex_init(&images_lock, nullptr);
    volatile bool stop_event = false;
    CameraThreadArgs thread_args = {&cameras, &latest_images, &images_lock, &stop_event};
    pthread_t capture_thread;
    if (pthread_create(&capture_thread, nullptr, run_camera_capture, &thread_args) != 0)
    {
        std::cerr << "Failed to create thread." << std::endl;
        return 1;
    }
    auto [context, cmd_socket, video_socket] = setup_zmq_sockets(robot_config.zmq);
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
                if (!cmd_socket.recv(msg, zmq::recv_flags::dontwait)) // 等待接收ZMQ消息
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
                        if (positions.is_array() && positions.size() >= robot_config.arm_motor_ids.size())
                        {
                            
                            for (size_t i = 0; i < robot_config.arm_motor_ids.size(); ++i)
                            {
                                for(auto &arm:arms)
                                {
                                    arm.second->joint_teleop_read[i]=positions[i];
                                }
                            }
                            for(auto &arm:arms)
                            {
                                arm.second->joint_teleop(arm.second->joint_teleop_read);
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
                        // 写入
                        last_cmd_time = time(nullptr);
                    }
                }
                catch (const std::exception &e) // 用于捕获异常
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
                //相机数据复制
                std::unordered_map<std::string, std::string> images_copy;
                vector<float> arm_obs_copy;
                float arm_obs[ARM_DOF]={0};

                pthread_mutex_lock(&images_lock);
                images_copy = latest_images;
                pthread_mutex_unlock(&images_lock);
                //机械臂观测数据复制
                for(auto &arm:arms)
                {
                    arm_obs_copy=arm.second->get_armstate();
                }
                for(int i=0;i<ARM_DOF;++i)
                {
                    arm_obs[i]=arm_obs_copy[i];
                }
                //车辆观测数据

                json observation = {
                    {"images", images_copy},
                    {"present_speed", {0, 0, 0}},
                    {"follower_arm_state", arm_obs}};

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