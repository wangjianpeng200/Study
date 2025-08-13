#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include "config.h"

using json = nlohmann::json;
using namespace std;

// 抽象机械臂类
class RoboticArm
{
protected:  
    vector<float> joint_obs;

public:
    vector<float> joint_obs;
    virtual void joint_teleop(const std::vector<float> &joint_teleop_read) = 0;
    // virtual void update(std::atomic<bool> &even_stop) = 0;
    virtual void get_armstate() = 0;
    // virtual void griper(const int value)=0;
    virtual ~RoboticArm() = default;
};


class Gen72_single : public RoboticArm
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
    {
        
        pthread_mutex_init(&this->arm_lock, NULL);
        stop_flag = false;
        float init_pose[7] = {0};   
        std::copy(config.init_pose.begin(), config.init_pose.end(), init_pose);   //设定初始化位置
        rm_init(RM_TRIPLE_MODE_E);
        this->robot_handle = rm_create_robot_handle(config.ip, 8080);
        int ret_init_move = rm_movej(this->robot_handle, init_pose, 30, 0, 0, 1);
        if (ret_init_move != 0)
        {
            std::cout << "init move failed" << std::endl;
        }
        int ret_set_rs485_mode = rm_set_tool_rs485_mode(this->robot_handle, 0, 115200);
        if (ret_set_rs485_mode != 0)
        {
            std::cout << "set rs485 mode failed" << std::endl;
        }
        this->Modebus_griper(100);
        set_realtime_push(config);
        pthread_create(&arm_state_thread, NULL, update, this);   //启动机械臂回调udp线程
    }

    ~Gen72();
    {
        stop_flag = true;
        rm_destroy_robot_handle(this->robot_handle);
        pthread_join(arm_state_thread, NULL);
        pthread_mutex_destroy(&arm_lock);
    }

    // 第三方夹爪-乐白控制函数
    void Modebus_griper(const int value)
    {
        rm_modbus_rtu_write_params_t param_write = {0};
        param_write.address = 40000;
        param_write.num = value;
        param_write.type = 1;
        param_write.device = 1;
        int ret_rm_write_modbus_rtu_registers = rm_write_modbus_rtu_registers(this->robot_handle, param_write);
    }

    // 跟随控制函数
    void joint_teleop(const std::vector<float> joint_teleop_read) override
    {
        float joint_send[7] = {0};
        for (int i = 0; i < 7; i++)
        {
            joint_send[i] = joint_teleop_read[i];
        }
        robot_service.rm_movej_canfd(this->robot_handle, joint_send, true, 0, 2, 50);
        // float giper_trans = (std::abs(joint_teleop_read[7] - 98.0) / 65.0) * 100.0;
        griper_value = joint_teleop_read[7];
        if ((griper_value < 21) && (this->gipflag == 1))
        {
            this->Modebus_griper(10);
            this->gipflag = 0;
        }
        // 状态为闭合，且需要张开夹爪
        if ((griper_value > 79) && (this->gipflag == 0))
        {
            this->Modebus_griper(100);
            this->gipflag = 1;
        }
    }

    void callback_rm_realtime_arm_joint_state(rm_realtime_arm_joint_state_t state)
    {
        // 检查数据解析错误码
        if (state.errCode == -3)
        {
            printf("Data parsing error: Data incomplete or format incorrect\n");
        }
        // 检查机械臂错误码
        if (state.arm_err != 0)
        {
            printf("Arm Error Code: %u\n", state.arm_err);
        }
        //检查系统错误码
        if (state.sys_err != 0)
        {
            printf("System Error Code: %u\n", state.sys_err);
        }
        pthread_mutex_lock(&arm_lock);  //机械臂加锁
        for(int i = 0; i < ARM_DOF; ++i)
        {
            this->joint_obs_read[i] = state.joint_status.joint_position[i];
        }
        pthread_mutex_unlock(&arm_lock);  //机械臂解锁

        // // 遍历并打印关节状态
        // for (int i = 0; i < ARM_DOF; ++i)
        // {
        //     printf("Joint %d Current: %.3f mA, Enabled: %s, Error Code: %u, Position: %.3f°, Temperature: %.3f°C, Voltage: %.3f V\n",
        //            i, state.joint_status.joint_current[i], state.joint_status.joint_en_flag[i] ? "true" : "false",
        //            state.joint_status.joint_err_code[i], state.joint_status.joint_position[i],
        //            state.joint_status.joint_temperature[i], state.joint_status.joint_voltage[i]);
        // }

        // 打印力传感器数据(需末端带有力传感器)
        // printf("Force Sensor Raw: [%.3f, %.3f, %.3f, %.3f, %.3f, %.3f] N/Nm\n",
        //        state.force_sensor.force[0], state.force_sensor.force[1], state.force_sensor.force[2],
        //        state.force_sensor.force[3], state.force_sensor.force[4], state.force_sensor.force[5]);
        // printf("Zero Force: [%.3f, %.3f, %.3f, %.3f, %.3f, %.3f] N/Nm\n",
        //        state.force_sensor.zero_force[0], state.force_sensor.zero_force[1], state.force_sensor.zero_force[2],
        //        state.force_sensor.zero_force[3], state.force_sensor.zero_force[4], state.force_sensor.zero_force[5]);
        // printf("Force Coordinate System: %d\n", state.force_sensor.coordinate);

        // 打印当前路点信息
        // printf("Current Waypoint Position: (%.3f, %.3f, %.3f) m\n",
        //        state.waypoint.position.x, state.waypoint.position.y, state.waypoint.position.z);
        // printf("Quaternion: (%.3f, %.3f, %.3f, %.3f)\n",
        //        state.waypoint.quaternion.w, state.waypoint.quaternion.x, state.waypoint.quaternion.y, state.waypoint.quaternion.z);
        // printf("Euler Angles: (%.3f, %.3f, %.3f) rad\n",
        //        state.waypoint.euler.rx, state.waypoint.euler.ry, state.waypoint.euler.rz);
    }

    vector<float> get_armstate()
    {
        pthread_mutex_lock(&arm_lock);  //机械臂加锁
        for(int i = 0; i < ARM_DOF; ++i)
        {
            this->joint_obs[i] = this->joint_obs_read[i];
        }
        pthread_mutex_unlock(&arm_lock);  //机械臂解锁
        return this->joint_obs;
    }

    void set_realtime_push(RobotConfigs robot_configs)
    {
        ip = robot_configs.ip;
        rm_realtime_push_config_t config;
        config.cycle = 5;
        config.enable = true;
        config.force_coordinate = 0;
        config.port = 8089;
        config.custom_config.expand_state = 0;
        config.custom_config.joint_speed = 0;
        config.custom_config.lift_state = 0;
        custom.custom_config.arm_current_status = 1;
        int ret_rm_set_realtime_push = rm_set_realtime_push(this->robot_handle, config);
        if (ret_rm_set_realtime_push != 0)
        {
            std::cout << "set realtime push failed" << std::endl;
        }
    }

    void update(std::atomic<bool> &even_stop) 
    {
        rm_realtime_arm_state_call_back(callback_rm_realtime_arm_joint_state);
        while(!even_stop)
        {
            int a=1;
            usleep(100000);
        }
    }
};

// 抽象相机类
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
