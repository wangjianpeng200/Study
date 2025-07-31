#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include"config.h"

using json = nlohmann::json;


//抽象机械臂类
class RoboticArm
{
public:
    virtual void joint_teleop(const std::vector<double>& joint_teleop_read)=0;
    virtual void update(std::atomic<bool>& even_stop)=0;
    virtual ~RoboticArm() = default;
};

class Gen72: public RoboticArm
{
public:
    rm_robot_handle *robot_handle;
    std::mutex arm_lock;
    int gipflag;
    int gipflag_send;
    std::map<std::string, double> leader_pos;
    std::vector<double> joint_teleop_write;
    std::vector<double> joint_teleop_read;
    std::vector<double> joint_obs_read;
    std::vector<double> joint_send;
    double gip_obs;
    rm_peripheral_read_write_params_t write_params;
    std::atomic<bool> stop_flag;
    std::condition_variable cv;
    std::mutex cv_mutex;

    Gen72(ArmConfig config);
    void joint_teleop(const std::vector<double>& joint_teleop_read) override;
    void update(std::atomic<bool>& even_stop) override;
};


class Gen72 {
private:
    rm_robot_handle *robot_handle;
    std::mutex arm_lock;
    int gipflag;
    int gipflag_send;
    std::map<std::string, double> leader_pos;
    std::vector<double> joint_teleop_write;
    std::vector<double> joint_teleop_read;
    std::vector<double> joint_obs_read;
    std::vector<double> joint_send;
    double gip_obs;
    rm_peripheral_read_write_params_t write_params;
    std::atomic<bool> stop_flag;
    std::condition_variable cv;
    std::mutex cv_mutex;
    
public:
    Gen72(RoboticArm config); 
    ~Gen72();
    void joint_teleop(const std::vector<double>& joint_teleop_read) override;
    void update(const RobotConfigs& robot_configs, std::atomic<bool>& even_stop) override;
    static void state_callback_adapter(const rm_robot_state_data& state_data, void* user_data);
    void arm_state_func(rm_robot_state_t* data);
};


//抽象相机类
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
    cv::Mat async_read() override;
    
private:
    cv::VideoCapture cap;
    int rotation;
};

