#include<Arm.h>

Gen72::Gen72(RoboticArm config)
{
    pthread_mutex_init(&this->arm_lock, NULL);
    stop_flag = false;
    float init_pose[7] = {0};
    std::copy(config.init_pose.begin(), config.init_pose.end(), init_pose); // 设定初始化位置
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
    pthread_create(&arm_state_thread, NULL, update, this); // 启动机械臂回调udp线程
}

Gen72::~Gen72()
{
    stop_flag = true;
    rm_destroy_robot_handle(this->robot_handle);
    pthread_join(arm_state_thread, NULL);
    pthread_mutex_destroy(&arm_lock);
}

// 第三方夹爪-乐白控制函数
void Gen72::Modebus_griper(const int value)
{
    rm_modbus_rtu_write_params_t param_write = {0};
    param_write.address = 40000;
    param_write.num = value;
    param_write.type = 1;
    param_write.device = 1;
    int ret_rm_write_modbus_rtu_registers = rm_write_modbus_rtu_registers(this->robot_handle, param_write);
}

// 跟随控制函数
void Gen72::joint_teleop(const std::vector<float> &joint_teleop_read)
{
    float joint_send[7] = {0};
    for (int i = 0; i < 7; i++)
    {
        joint_send[i] = joint_teleop_read[i];
    }
    robot_service.rm_movej_canfd(this->robot_handle, joint_send, true, 0, 2, 50);
    // float giper_trans = (std::abs(joint_teleop_read[7] - 98.0) / 65.0) * 100.0;
    float griper_value = joint_teleop_read[7];
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

void Gen72::callback_rm_realtime_arm_joint_state(rm_realtime_arm_joint_state_t state)
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
    // 检查系统错误码
    if (state.sys_err != 0)
    {
        printf("System Error Code: %u\n", state.sys_err);
    }
    pthread_mutex_lock(&arm_lock); // 机械臂加锁
    for (int i = 0; i < ARM_DOF; ++i)
    {
        this->joint_obs_read[i] = state.joint_status.joint_position[i];
    }
    pthread_mutex_unlock(&arm_lock); // 机械臂解锁
}

vector<float> Gen72::get_armstate()
{
    pthread_mutex_lock(&arm_lock); // 机械臂加锁
    for (int i = 0; i < ARM_DOF; ++i)
    {
        this->joint_obs[i] = this->joint_obs_read[i];
    }
    pthread_mutex_unlock(&arm_lock); // 机械臂解锁
    return this->joint_obs;
}

void Gen72::set_realtime_push(RobotConfigs robot_configs)
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

void Gen72::update(std::atomic<bool> &even_stop)
{
    rm_realtime_arm_state_call_back(callback_rm_realtime_arm_joint_state);
    while (!even_stop)
    {
        int a = 1;
        usleep(100000);
    }
}