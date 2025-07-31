#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

using json = nlohmann::json;

struct CameraConfig
{
    std::string type;
    std::string device;
    int fps;
    int width;
    int height;
    int rotation;
};

struct ZMQConfig
{
    std::string ip;
    int command_port;
    int video_port;
};

struct ArmConfig
{
    std::string type;
    std::string ip;
    std::vector<int> init_pose;
};

struct RobotConfig
{
    std::unordered_map<std::string, CameraConfig> cameras;
    std::unordered_map<std::string, ArmConfig> arms;
    std::vector<std::string> arm_motor_ids;
    ZMQConfig zmq;
};

class ConfigLoader
{
public:
    static RobotConfig loadFromFile(const std::string &filepath);
    static void saveToFile(const RobotConfig &config, const std::string &filepath);

private:
    static CameraConfig parseCameraConfig(const json &camera_json);
    static std::vector<std::string> parseArmMotorIds(const json &arm_motor_ids_json);
    static ZMQConfig parseZMQConfig(const json &zmq_json);
    static ArmConfig parseArmConfig(const json &arm_json);
};

#endif // CONFIG_LOADER_H