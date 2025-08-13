#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>
#include <array>
#include <mutex>
#include <atomic>
#include <pthread.h>

// Forward declarations for serial communication
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

struct ChassiConfig
{
    std::string type;
    std::string device;
    std::int baudrate;
};

struct ArmConfig
{
    std::string type;
    std::string ip;
    std::vector<int> init_pose;
};

struct ZMQConfig
{
    std::string ip;
    int command_port;
    int video_port;
};


struct RobotConfig
{
    std::unordered_map<std::string, CameraConfig> cameras;
    std::unordered_map<std::string, ArmConfig> arms;
    ChassiConfig chassis;
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
    static ChassiConfig parseChassiConfig(const json &chassis_json);
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