#include "config_loader.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

CameraConfig ConfigLoader::parseCameraConfig(const json &camera_json)
{
    CameraConfig config;
    config.type = camera_json.value("type", "");
    config.device = camera_json.value("device", "");
    config.fps = camera_json.value("fps", 30);
    config.width = camera_json.value("width", 640);
    config.height = camera_json.value("height", 480);
    config.rotation = camera_json.value("rotation", 0);
    return config;
}

ZMQConfig ConfigLoader::parseZMQConfig(const json &zmq_json)
{
    ZMQConfig config;
    config.ip = zmq_json.value("ip", "*");
    config.command_port = zmq_json.value("command_port", 5555);
    config.video_port = zmq_json.value("video_port", 5556);
    return config;
}

ArmConfig ConfigLoader::parseArmConfig(const json &arm_json)
{
    ArmConfig config;
    config.type = arm_json.value("type", "");
    config.which = arm_json.value("which", "");
    config.ip = arm_json.value("ip", "");
    return config;
}

std::vector<std::string> ConfigLoader::parseArmMotorIds(const json &arm_motor_ids_json)
{
    std::vector<std::string> motor_ids;
    for (auto &motor_id : arm_motor_ids_json)
    {
        motor_ids.push_back(motor_id.get<std::string>());
    }
    return motor_ids;
}

RobotConfig ConfigLoader::loadFromFile(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open config file: " + filepath);
    }
    json config_json;
    file >> config_json;
    file.close();

    RobotConfig config;

    // 解析相机配置
    if (config_json.contains("robot") && config_json["robot"].contains("cameras"))
    {
        auto cameras_json = config_json["robot"]["cameras"];
        for (auto it = cameras_json.begin(); it != cameras_json.end(); ++it)
        {
            config.cameras[it.key()] = parseCameraConfig(it.value());
        }
    }

    if(config_json.contains("robot") && config_json["robot"].contains("arms"))
    {
        auto arms_json = config_json["robot"]["arms"];
        for (auto it = arms_json.begin(); it != arms_json.end(); ++it)
        {
            config.arms[it.key()] = parseArmConfig(it.value());
        }
    }

    if(config_json.contains("robot") && config_json["robot"].contains("arm_motor_ids"))
    {
        config.arm_motor_ids = parseArmMotorIds(config_json["robot"]["arm_motor_ids"]);
    }
    // 解析手臂配置
    if (config_json.contains("robot") && config_json["robot"].contains("arms"))
    {
        auto arms_json = config_json["robot"]["arms"];
        for (auto it = arms_json.begin(); it != arms_json.end(); ++it)
        {
            config.arms[it.key()] = parseArmConfig(it.value());
        }
    }

    // 解析ZMQ配置
    if (config_json.contains("zmq"))
    {
        config.zmq = parseZMQConfig(config_json["zmq"]);
    }

    return config;
}

void ConfigLoader::saveToFile(const RobotConfig &config, const std::string &filepath)
{
    json config_json;

    // 构建相机配置
    for (const auto &[name, camera_config] : config.cameras)
    {
        config_json["robot"]["cameras"][name] = {
            {"type", camera_config.type},
            {"device", camera_config.device},
            {"fps", camera_config.fps},
            {"width", camera_config.width},
            {"height", camera_config.height},
            {"rotation", camera_config.rotation}};
    }

    // 构建手臂配置
    for (const auto &[name, arm_config] : config.arms)
    {
        config_json["robot"]["arms"][name] = {
            {"type", arm_config.type},
            {"which", arm_config.which},
            {"ip", arm_config.ip}};
    }

    // 构建ZMQ配置
    config_json["zmq"] = {
        {"ip", config.zmq.ip},
        {"command_port", config.zmq.command_port},
        {"video_port", config.zmq.video_port}};

    // 写入文件
    std::ofstream file(filepath);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file for writing: " + filepath);
    }
    file << config_json.dump(4); // 4 spaces for indentation
    file.close();
}