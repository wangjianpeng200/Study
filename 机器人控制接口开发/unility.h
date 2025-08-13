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

// 抽象相机类
class Camera
{
public:
    virtual cv::Mat async_read() = 0;
    virtual ~Camera() = default;
};

// 抽象机械臂类
class RoboticArm
{
protected:
    vector<float> joint_obs;

public:
    vector<float> joint_teleop_write;
    vector<float> joint_obs;
    virtual void joint_teleop(const std::vector<float> &joint_teleop_read) = 0;
    virtual void get_armstate() = 0;
    virtual ~RoboticArm() = default;
};

struct Chassis_data
{
public:
    double vx, vy, wz;
    double px, py, pz;
    // 添加默认构造函数
    Chassis_data() :  vx(0.0), vy(0.0), wz(0.0), px(0.0), py(0.0), pz(0.0) {}
};

class Chassis
{
public:
    static Chassis_data chassis_data;
    virtual bool send_speed_to_chassis(double x, double y, double w) = 0;     //发送数据
    virtual void update_thread_function(void* arg) = 0;  //更新数据
    virtual Chassis_data get_chassis_data() = 0;  //获取数据
    virtual ~Chassis() = default;  
};


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

