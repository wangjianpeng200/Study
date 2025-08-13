
#include<unility.h>


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


