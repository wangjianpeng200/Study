#include<unility.h>


class Mick_Chassis : public Chassis
{
private:
    int serial_fd;
    int timeout;
    double speed_offset;
    bool stop_flag;
    pthread_mutex_t mick_lock;  
    pthread_t thread_id;
    static float vx, vy, wz;

    int init_serial(const char *port, int baudrate, int timeout);  //初始化串口
    std::vector<uint8_t> read_serial();  //读取串口数据
    bool analy_uart_recive_data(const std::vector<uint8_t> &serial_data); // 分析串口接收到的数据
    std::vector<uint8_t> pack_speed(double v); //打包速度数据，数据偏移和单位换算

public:
    Mick_Chassis(/*const ChassisConfig config*/); // 简化构造函数参数
    ~Mick_Chassis();
    bool send_speed_to_chassis(double x, double y, double w) override;     //修正函数名以匹配基类
    void cmd_vel_callback(double linear_x, double angular_z, int chassis_type);    //回调函数，用于接收速度指令
    static void* update_thread_function(void *arg);  // 线程函数必须是静态的
    Chassis_data get_chassis_data() override; // 修正返回类型和参数
};


