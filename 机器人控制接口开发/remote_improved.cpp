#include <opencv2/opencv.hpp>
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include <functional>
#include <b64/encode.h>
#include <zmq.hpp>
#include <nlohmann/json.hpp>

#include "config_loader.h"
#include "new_factory.h"
#include "lekiwi.h"

using json = nlohmann::json;

// 抽象设备接口
class Device {
public:
    virtual ~Device() = default;
    virtual void execute(const json& command) = 0;
    virtual json getObservation() = 0;
};

// 抽象工厂接口
class DeviceFactory {
public:
    virtual ~DeviceFactory() = default;
    virtual std::unique_ptr<Device> createDevice(const std::string& type, const json& config) = 0;
};

// 相机设备实现
class CameraDevice : public Device {
private:
    std::unique_ptr<Camera> camera;
    std::string name;
    mutable std::mutex frame_mutex;
    cv::Mat latest_frame;

public:
    CameraDevice(const std::string& name, const CameraConfig& config) : name(name) {
        if (config.type == "opencv") {
            camera = std::make_unique<OpenCVCamera>(
                config.device,
                config.fps,
                config.width,
                config.height,
                config.rotation);
        } else {
            throw std::runtime_error("Unsupported camera type: " + config.type);
        }
    }

    void execute(const json& command) override {
        // 相机设备通常不需要执行命令，主要用于获取观测数据
        std::lock_guard<std::mutex> lock(frame_mutex);
        latest_frame = camera->async_read();
    }

    json getObservation() override {
        std::lock_guard<std::mutex> lock(frame_mutex);
        if (latest_frame.empty()) {
            return nullptr;
        }
        
        std::vector<uchar> buffer;
        cv::imencode(".jpg", latest_frame, buffer);
        std::string encoded = base64_encode(buffer.data(), buffer.size());
        return {
            {"type", "camera"},
            {"name", name},
            {"data", encoded}
        };
    }
};

// 机械臂设备实现
class ArmDevice : public Device {
private:
    std::unique_ptr<RoboticArm> arm;
    std::string name;

public:
    ArmDevice(const std::string& name, const ArmConfig& config) : name(name) {
        if (config.type == "gen72") {
            // 注意：这里可能需要调整，因为Gen72构造函数可能需要不同的参数
            // 这里假设有一个合适的构造函数
            arm = std::make_unique<Gen72>(/* appropriate parameters */);
        } else {
            throw std::runtime_error("Unsupported arm type: " + config.type);
        }
    }

    void execute(const json& command) override {
        if (command.contains("arm_positions")) {
            auto positions = command["arm_positions"];
            if (positions.is_array() && positions.size() >= /* arm DOF */) {
                std::vector<float> joint_positions;
                for (const auto& pos : positions) {
                    joint_positions.push_back(pos.get<float>());
                }
                arm->joint_teleop(joint_positions);
            }
        }
    }

    json getObservation() override {
        auto state = arm->get_armstate();
        return {
            {"type", "arm"},
            {"name", name},
            {"state", state}
        };
    }
};

// 轮子设备实现
class WheelDevice : public Device {
private:
    std::string name;
    int left_speed, back_speed, right_speed;
    std::time_t last_command_time;

public:
    WheelDevice(const std::string& name) : name(name), left_speed(0), back_speed(0), right_speed(0) {
        last_command_time = std::time(nullptr);
    }

    void execute(const json& command) override {
        if (command.contains("raw_velocity")) {
            auto wheel_data = command["raw_velocity"];
            left_speed = wheel_data.value("left_wheel", 0);
            back_speed = wheel_data.value("back_wheel", 0);
            right_speed = wheel_data.value("right_wheel", 0);
            last_command_time = std::time(nullptr);
            std::cout << "[INFO] Setting wheels to (" << left_speed << ", " << back_speed << ", " << right_speed << ")" << std::endl;
        }
        
        // 看门狗：无命令则停止机器人
        if (std::time(nullptr) - last_command_time > 0.5) {
            left_speed = back_speed = right_speed = 0;
            std::cout << "[INFO] No command received, stopping robot." << std::endl;
        }
    }

    json getObservation() override {
        return {
            {"type", "wheels"},
            {"name", name},
            {"present_speed", {left_speed, back_speed, right_speed}}
        };
    }
};

// 相机工厂实现
class CameraFactory : public DeviceFactory {
public:
    std::unique_ptr<Device> createDevice(const std::string& type, const json& config) override {
        if (type == "camera") {
            // 从JSON配置中提取CameraConfig
            CameraConfig camConfig;
            camConfig.type = config.value("type", "");
            camConfig.device = config.value("device", 0);
            camConfig.fps = config.value("fps", 30);
            camConfig.width = config.value("width", 640);
            camConfig.height = config.value("height", 480);
            camConfig.rotation = config.value("rotation", 0);
            
            return std::make_unique<CameraDevice>(config.value("name", "camera"), camConfig);
        }
        return nullptr;
    }
};

// 机械臂工厂实现
class ArmFactory : public DeviceFactory {
public:
    std::unique_ptr<Device> createDevice(const std::string& type, const json& config) override {
        if (type == "arm") {
            // 从JSON配置中提取ArmConfig
            ArmConfig armConfig;
            armConfig.type = config.value("type", "");
            // 其他配置项...
            
            return std::make_unique<ArmDevice>(config.value("name", "arm"), armConfig);
        }
        return nullptr;
    }
};

// 轮子工厂实现
class WheelFactory : public DeviceFactory {
public:
    std::unique_ptr<Device> createDevice(const std::string& type, const json& config) override {
        if (type == "wheels") {
            return std::make_unique<WheelDevice>(config.value("name", "wheels"));
        }
        return nullptr;
    }
};

// 设备管理器
class DeviceManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Device>> devices;
    std::unordered_map<std::string, std::unique_ptr<DeviceFactory>> factories;

public:
    DeviceManager() {
        // 注册工厂
        factories["camera"] = std::make_unique<CameraFactory>();
        factories["arm"] = std::make_unique<ArmFactory>();
        factories["wheels"] = std::make_unique<WheelFactory>();
    }

    void addDevice(const std::string& name, const std::string& type, const json& config) {
        auto factoryIt = factories.find(type);
        if (factoryIt != factories.end()) {
            devices[name] = factoryIt->second->createDevice(type, config);
        } else {
            throw std::runtime_error("Unknown device type: " + type);
        }
    }

    void executeCommand(const std::string& deviceName, const json& command) {
        auto it = devices.find(deviceName);
        if (it != devices.end()) {
            it->second->execute(command);
        } else {
            throw std::runtime_error("Device not found: " + deviceName);
        }
    }

    void executeAllCommands(const json& command) {
        for (auto& [name, device] : devices) {
            // 这里可以根据命令类型决定发送给哪些设备
            device->execute(command);
        }
    }

    json getObservations() {
        json observations;
        for (const auto& [name, device] : devices) {
            observations.push_back(device->getObservation());
        }
        return observations;
    }
};

// ZMQ通信管理器
class ZMQManager {
private:
    zmq::context_t context;
    zmq::socket_t cmd_socket;
    zmq::socket_t video_socket;

public:
    ZMQManager(const ZMQConfig& config) : context(1), cmd_socket(context, ZMQ_PULL), video_socket(context, ZMQ_PUSH) {
        cmd_socket.set(zmq::sockopt::conflate, 1);
        cmd_socket.bind("tcp://" + config.ip + ":" + std::to_string(config.port));
        video_socket.set(zmq::sockopt::conflate, 1);
        video_socket.bind("tcp://" + config.ip + ":" + std::to_string(config.video_port));
    }

    bool receiveCommand(json& command) {
        zmq::message_t msg;
        if (cmd_socket.recv(msg, zmq::recv_flags::dontwait)) {
            try {
                command = json::parse(msg.to_string());
                return true;
            } catch (const std::exception& e) {
                std::cerr << "[ERROR] Parsing message failed: " << e.what() << std::endl;
            }
        }
        return false;
    }

    void sendObservations(const json& observations) {
        try {
            video_socket.send(zmq::message_t(observations.dump()), zmq::send_flags::none);
        } catch (const zmq::error_t& e) {
            std::cerr << "[ERROR] Failed to send observation: " << e.what() << std::endl;
        }
    }
};

std::string base64_encode(const unsigned char* data, size_t len) {
    const size_t encoded_size = b64_encoded_size(len);
    std::string result(encoded_size, '\0');
    b64_encode(data, len, result.data(), encoded_size);
    return result;
}

int main() {
    try {
        // 1. 加载机器人配置
        RobotConfig robot_config = ConfigLoader::loadFromFile("config.json");

        // 2. 创建设备管理器
        DeviceManager device_manager;

        // 3. 根据配置创建设备
        for (const auto& [name, config] : robot_config.cameras) {
            json camJson;
            camJson["name"] = name;
            camJson["type"] = config.type;
            camJson["device"] = config.device;
            camJson["fps"] = config.fps;
            camJson["width"] = config.width;
            camJson["height"] = config.height;
            camJson["rotation"] = config.rotation;
            device_manager.addDevice(name, "camera", camJson);
        }

        for (const auto& [name, config] : robot_config.arms) {
            json armJson;
            armJson["name"] = name;
            armJson["type"] = config.type;
            // 添加其他配置项
            device_manager.addDevice(name, "arm", armJson);
        }

        // 添加轮子设备
        json wheelsJson;
        wheelsJson["name"] = "wheels";
        device_manager.addDevice("wheels", "wheels", wheelsJson);

        // 4. 初始化ZMQ通信
        ZMQManager zmq_manager(robot_config.zmq);

        std::cout << "LeKiwi robot server started. Waiting for commands..." << std::endl;

        // 5. 主循环
        while (true) {
            // 处理所有待处理的命令
            json command;
            while (zmq_manager.receiveCommand(command)) {
                device_manager.executeAllCommands(command);
            }

            // 获取所有设备的观测数据
            json observations = device_manager.getObservations();
            zmq_manager.sendObservations(observations);

            // 控制循环频率约30Hz
            std::this_thread::sleep_for(std::chrono::milliseconds(33));
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Runtime error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}