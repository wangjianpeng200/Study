#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include "config.h"
#include <vector>
#include <array>
#include <mutex>
#include <atomic>
#include <pthread.h>

// Forward declarations for serial communication
using json = nlohmann::json;
using namespace std;

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

class Chassis
{
private:
    int chassis_type;
    float vx, vy, wz;
    float px, py, pz;
public:
    
}


class chassis
{
    int chassis_type;
    float vx, vy, wz;
    float px, py, pz;
    std::vector<MotorMeasure> motor_measures;
    Chassis(const Chassis &other) = delete;
    Chassis() {}
}

// 具体机械臂类
class Gen72 : public RoboticArm
{
private:
    rm_robot_handle *robot_handle;
    pthread_t arm_state_thread;
    std::mutex arm_lock;
    int gipflag = 1;
    std::array<double, 7> joint_teleop_read = {0};
    std::array<double, 7> joint_obs_read = {0};
    vector<float> joint_obs;
    int gip_obs = 0;
    std::atomic<bool> stop_flag;

public:
    Gen72(RoboticArm config);
    ~Gen72();

    // 第三方夹爪-乐白控制函数
    void Modebus_griper(const int value);
    // 跟随控制函数
    void joint_teleop(const std::vector<float> &joint_teleop_read) override;
    void callback_rm_realtime_arm_joint_state(rm_realtime_arm_joint_state_t state);
    vector<float> get_armstate();
    void set_realtime_push(RobotConfigs robot_configs);
    void update(std::atomic<bool> &even_stop);
};

// 具体相机类
class OpenCVCamera : public Camera
{
public:
    OpenCVCamera(const std::string &device, int fps, int width, int height, int rotation); // 初始化
    cv::Mat async_read() override;                                                         // 异步读取帧
    ~OpenCVCamera();

private:
    cv::VideoCapture cap;
    int rotation;
};


class SerialPort;

struct Chassis {
    int available = 0;
    float vx = 0.0f, vy = 0.0f, wz = 0.0f;
    float px = 0.0f, py = 0.0f, pz = 0.0f;
    int chassis_type = 0;  // 0:X4  1:M4  2:Ackermann  3:4WS4WD
    int motor_type = 0;
};

struct MotorMeasure {
    int speed_rpm = 0;
    int round_cnt = 0;
    int angle = 0;
};


class X4ChassisController {
private:
    SerialPort* ser;
    int speed_offset = 10;  // 速度偏移值，用于将负数转换为正数
    std::vector<MotorMeasure> moto_chassis;
    Chassis chassis;

    SerialPort* init_serial(const std::string& port, int baudrate, int timeout);
    std::vector<uint8_t> read_serial(SerialPort* port);
    void send_speed_to_X4chassis(float x, float y, float w);
    bool analy_uart_recive_data(const std::vector<uint8_t>& serial_data);

public:
    X4ChassisController(const std::string& port = "/dev/ttyUSB0", int baudrate = 115200, int timeout = 1);
    ~X4ChassisController();
    
    void cmd_vel_callback(float linear_x, float angular_z, int chassis_type);
    bool updata(/* Add appropriate parameters for mick_lock and stop_event */);
};
