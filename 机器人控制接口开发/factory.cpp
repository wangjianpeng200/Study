#include "factory.h"

// RoboticArm类的纯虚析构函数定义
RoboticArm::~RoboticArm() = default;

// gen72类的静态回调适配器函数实现
void gen72::state_callback_adapter(const rm_robot_state_data &state_data, void *user_data)
{
    if (user_data)
    {
        gen72 *arm_instance = static_cast<gen72 *>(user_data);
        arm_instance->arm_state_func(state_data);
    }
}

// gen72类的构造函数实现
gen72::gen72(ArmConfig config) : robot_handle(nullptr)
{
    // 初始化机械臂句柄
    // robot_handle = rm_init_robot_arm(config.canfd_channel.c_str(), config.arm_type, 100);
    // if (!robot_handle) {
    //     std::cerr << "Failed to initialize robot arm" << std::endl;
    //     return;
    // }
    //
    // // 设置状态回调函数
    // rm_set_realtime_push(robot_handle, true, 200);
    // rm_set_arm_state_callback(robot_handle, gen72::state_callback_adapter, this);
    //
    // // 移动到初始位置
    // std::vector<float> initial_joint_angles = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    // rm_movej_canfd(robot_handle, initial_joint_angles, true, 0, 2, 200);
}

// gen72类的arm_state_func方法实现
void gen72::arm_state_func(const rm_robot_state_data &state_data)
{
    // 在这里处理机械臂状态数据
    // 例如，可以更新关节角度、末端位置等成员变量
}

// gen72类的joint_teleop方法实现
void gen72::joint_teleop(const std::vector<double> &joint_teleop_read)
{
    std::vector<float> joint_teleop_write;
    joint_teleop_write.reserve(joint_teleop_read.size());
    for (const auto &angle : joint_teleop_read)
    {
        joint_teleop_write.push_back(static_cast<float>(angle));
    }

    // 发送关节角度指令
    // rm_movej_canfd(robot_handle, joint_teleop_write, true, 0, 2, 200);

    // 控制夹爪
    // rm_write_single_register(robot_handle, write_params, 10);
    // rm_write_single_register(robot_handle, write_params, 100);
}

// gen72类的update方法实现
void gen72::update(std::atomic<bool> &even_stop)
{
    // 配置实时推送
    // rm_set_realtime_push(robot_handle, true, 200);
    // rm_get_realtime_push(robot_handle);

    while (!even_stop.load())
    {
        // 主循环逻辑
        // rm_realtime_arm_state_call_back(robot_handle);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Gen72类的构造函数实现
Gen72::Gen72()
    : robot_handle(nullptr),
      gipflag(1),
      gipflag_send(1),
      gip_obs(0.0),
      write_params{1, 40000, 1},
      stop_flag(false)
{
    // 初始化关节向量
    joint_teleop_write = std::vector<double>(7, 0.0);
    joint_teleop_read = std::vector<double>(7, 0.0);
    joint_obs_read = std::vector<double>(7, 0.0);
    joint_send = std::vector<double>(7, 0.0);

    // 机械臂初始化代码应该在这里添加
    // robot_handle = rm_init_robot_arm("can0", "gen72", 100);
    // if (!robot_handle) {
    //     std::cerr << "Failed to initialize robot arm" << std::endl;
    //     return;
    // }
    //
    // // 设置机械臂参数
    // rm_set_arm_run_mode(robot_handle, 2);
    // rm_set_tool_voltage(robot_handle, 3);
    // rm_set_modbus_mode(robot_handle, 1, 115200, 2);
    // rm_write_single_register(robot_handle, write_params, 100);
    // rm_change_tool_frame(robot_handle, "lebai2");
    //
    // // 移动到基础位置
    // std::vector<float> joint_base(7, 0.0);
    // rm_movej(robot_handle, joint_base, 20, 0, 0, 1);
}

// Gen72类的析构函数实现
Gen72::~Gen72()
{
    // 释放机械臂资源
    // if (robot_handle) {
    //     rm_release_robot_arm(robot_handle);
    // }
}

// Gen72类的joint_teleop方法实现
void Gen72::joint_teleop(const std::vector<double> &joint_teleop_read)
{
    if (joint_teleop_read.size() < 8)
        return; // 确保输入有足够数据

    for (int i = 0; i < 7; ++i)
    {
        this->joint_teleop_read[i] = joint_teleop_read[i];
    }

    // 关节角度转换
    joint_teleop_write = joint_teleop_read;
    joint_teleop_write[3] = -joint_teleop_write[3];
    joint_teleop_write[5] = -joint_teleop_write[5];

    // 发送关节角度指令
    // rm_movej_canfd(robot_handle, joint_teleop_write, true, 0, 2, 200);

    // 夹爪控制逻辑
    double giper_trans = (std::fabs(joint_teleop_read[7] - 98.0) / (98.0 - 33.0)) * 100.0;
    giper_trans = std::round(giper_trans * 100.0) / 100.0; // 保留两位小数

    // 控制夹爪
    // if (giper_trans < 21 && gipflag == 1) {
    //     rm_write_single_register(robot_handle, write_params, 10);
    //     gipflag = 0;
    // }
    // else if (giper_trans > 79 && gipflag == 0) {
    //     rm_write_single_register(robot_handle, write_params, 100);
    //     gipflag = 1;
    // }
    gip_obs = giper_trans;
}

// Gen72类的静态回调适配器函数实现
void Gen72::arm_state_callback_wrapper(rm_robot_state_t *data, void *user_data)
{
    Gen72 *instance = static_cast<Gen72 *>(user_data);
    if (instance)
    {
        instance->arm_state_func(data);
    }
}

// Gen72类的arm_state_func方法实现
void Gen72::arm_state_func(rm_robot_state_t *data)
{
    // auto joint_status = data->joint_status.to_dict();
    // std::lock_guard<std::mutex> lock(arm_lock);
    // // 实际填充关节数据（示例）
    // for (int i = 0; i < 7; ++i) {
    //     joint_obs_read[i] = joint_status["joint" + std::to_string(i)];
    // }
}

// Gen72类的update方法实现
void Gen72::update(const RobotConfigs &robot_configs, std::atomic<bool> &even_stop)
{
    // rm_udp_custom_config_t custom;
    // custom.joint_speed = 0;
    // custom.lift_state = 0;
    // custom.expand_state = 0;
    // custom.arm_current_status = 1;
    //
    // rm_realtime_push_config_t config(4, true, 8089, 0, robot_configs.ip_rml, custom);
    // std::cout << rm_set_realtime_push(robot_handle, config) << std::endl;
    // std::cout << rm_get_realtime_push(robot_handle) << std::endl;
    // // 注册状态回调（使用静态适配器）
    // rm_realtime_arm_state_call_back(robot_handle, Gen72::arm_state_callback_wrapper, this);

    // 主循环
    while (!even_stop.load())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


// OpenCVCamera类的async_read方法实现
cv::Mat OpenCVCamera::async_read()
{
    cv::Mat frame, rotated;
    if (cap.read(frame))
    {
        cv::rotate(frame, rotated, static_cast<cv::RotateFlags>(rotation));
        return rotated;
    }
    return cv::Mat(); // 返回空矩阵表示失败
}
