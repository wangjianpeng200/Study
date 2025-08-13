#include<Chassis_mick.h>

Mick_Chassis::Mick_Chassis(const ChassisConfig config)
: serial_fd(-1), speed_offset(10.0), timeout(1), vx(0.0), vy(0.0), wz(0.0)
{
    std::string port = config.port;
    int baudrate = config.baudrate;
    serial_fd = init_serial(port, baudrate, timeout);   //初始化串口
    pthread_mutex_init(&mick_lock, NULL); 
    pthread_create(&thread_id, NULL, update_thread_function, this);
}

Mick_Chassis::~Mick_Chassis()
{
    if (serial_fd != -1)
    {
        close(serial_fd);
    }
    stop_flag = true;
    pthread_mutex_destroy(&mick_lock);
    pthread_join(thread_id, NULL);
}

int Mick_Chassis::init_serial(const char *port, int baudrate, int timeout)
{
    int fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
        std::cerr << "Failed to open serial port: " << port << std::endl;
        return -1;
    }

    struct termios options;
    tcgetattr(fd, &options);

    // 设置波特率
    speed_t baud = B115200;
    switch (baudrate)
    {
    case 9600:
        baud = B9600;
        break;
    case 19200:
        baud = B19200;
        break;
    case 38400:
        baud = B38400;
        break;
    case 57600:
        baud = B57600;
        break;
    case 115200:
        baud = B115200;
        break;
    default:
        baud = B115200;
        break;
    }
    cfsetispeed(&options, baud);
    cfsetospeed(&options, baud);
    // 设置数据位、停止位、校验位
    options.c_cflag &= ~PARENB; // 无校验
    options.c_cflag &= ~CSTOPB; // 1位停止位
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8; // 8位数据位

    // 禁用硬件流控
    options.c_cflag &= ~CRTSCTS;

    // 启用接收
    options.c_cflag |= (CLOCAL | CREAD);

    // 设置超时
    options.c_cc[VTIME] = timeout * 10; 
    options.c_cc[VMIN] = 0;

    tcsetattr(fd, TCSANOW, &options);
    tcflush(fd, TCIOFLUSH);

    std::cout << "串口 " << port << " 已打开，波特率 " << baudrate << std::endl;
    return fd;
}

std::vector<uint8_t> Mick_Chassis::read_serial()
{
    std::vector<uint8_t> data;
    if (serial_fd == -1)
    {
        return data;
    }
    int bytes_available = 0;
    ioctl(serial_fd, FIONREAD, &bytes_available);
    if (bytes_available > 0)
    {
        data.resize(bytes_available);
        read(serial_fd, data.data(), bytes_available);
    }
    return data;
}

std::vector<uint8_t> Mick_Chassis::pack_speed(double v)
{
    int scaled = static_cast<int>((v + speed_offset) * 100);
    return {static_cast<uint8_t>((scaled >> 8) & 0xFF), static_cast<uint8_t>(scaled & 0xFF)};
}

bool Mick_Chassis::send_speed_to_chassis(double x, double y, double w)
{
    if (serial_fd == -1)
    {
        std::cout << "串口未连接" << std::endl;
        return false;
    }

    std::vector<uint8_t> data_tem = {0xAE, 0xEA, 0x00, 0xF3};

    // 添加速度数据
    auto x_speed = pack_speed(x);
    auto y_speed = pack_speed(y);
    auto w_speed = pack_speed(w);

    data_tem.insert(data_tem.end(), x_speed.begin(), x_speed.end());
    data_tem.insert(data_tem.end(), y_speed.begin(), y_speed.end());
    data_tem.insert(data_tem.end(), w_speed.begin(), w_speed.end());
    data_tem.insert(data_tem.end(), {0x00, 0x00}); // 保留位

    // 计算校验和
    uint8_t checksum = 0;
    for (size_t i = 2; i < data_tem.size(); ++i)
    {
        checksum += data_tem[i];
    }
    checksum = 0xFF - checksum;

    data_tem.push_back(checksum);
    data_tem[2] = static_cast<uint8_t>(data_tem.size() - 2); // 数据长度
    data_tem.insert(data_tem.end(), {0xEF, 0xFE});

    ssize_t result = write(serial_fd, data_tem.data(), data_tem.size());
    if (result == -1)
    {
        std::cout << "发送失败" << std::endl;
        return false;
    }

    return true;
}

bool Mick_Chassis::analy_uart_recive_data(const std::vector<uint8_t> &serial_data)
{
    std::vector<uint8_t> reviced_tem;
    bool rec_flag = false;
    uint8_t tem_last = 0, tem_curr = 0;
    int header_count = 0;
    size_t step = 0;

    // 帧头检测
    for (size_t i = 0; i < serial_data.size(); ++i)
    {
        tem_last = tem_curr;
        tem_curr = serial_data[i];
        if (!rec_flag)
        {
            if (tem_last == 0xAE && tem_curr == 0xEA)
            {
                rec_flag = true;
                reviced_tem.push_back(tem_last);
                reviced_tem.push_back(tem_curr);
            }
        }
        else
        {
            reviced_tem.push_back(tem_curr);
            if (tem_last == 0xEF && tem_curr == 0xFE)
            {
                header_count++;
                rec_flag = false;
            }
        }
    }

    for (int k = 0; k < header_count; ++k)
    {
        if (step + 2 >= reviced_tem.size())
        {
            break;
        }

        uint8_t LL = reviced_tem[step + 2];
        size_t frame_len = LL + 4;

        if (reviced_tem[step] != 0xAE || reviced_tem[step + 1] != 0xEA ||
            reviced_tem[step + frame_len - 2] != 0xEF || reviced_tem[step + frame_len - 1] != 0xFE)
        {
            step++;
            continue;
        }

        if (reviced_tem[step + 3] == 0xA7)
        {
            size_t offset = step + 4;
            try
            {
                // 解析速度数据
                int16_t vx_raw = static_cast<int16_t>((reviced_tem[offset] << 8) | reviced_tem[offset + 1]);
                int16_t vy_raw = static_cast<int16_t>((reviced_tem[offset + 2] << 8) | reviced_tem[offset + 3]);
                int16_t wz_raw = static_cast<int16_t>((reviced_tem[offset + 4] << 8) | reviced_tem[offset + 5]);

                vx = static_cast<double>(vx_raw) / 1000.0;
                vy = static_cast<double>(vy_raw) / 1000.0;
                wz = static_cast<double>(wz_raw) / 1000.0;
                return true;
            }
            catch (...)
            {
                std::cout << "解析数据失败" << std::endl; // 修正: 添加std::命名空间
            }
        }
        step += frame_len;
    }
    return false;
}

// 静态线程函数实现
void* Mick_Chassis::update_thread_function(void *arg) override
{
    while (!stop_flag)
    {
        // 读取串口数据
        std::vector<uint8_t> serial_data = read_serial();
        if (!serial_data.empty())
        {
            bool uart_recive_flag = analy_uart_recive_data(serial_data);
            if (uart_recive_flag)
            {
                pthread_mutex_lock(mick_lock);
                chassis_data.vx = vx;
                chassis_data.vy = vy;
                chassis_data.wz = wz;
                pthread_mutex_unlock(mick_lock);
            }
        }
        // 延时60ms
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
    return nullptr;
}

Chassis_data Mick_Chassis::get_chassis_data() // 修正: 移除参数，修正返回类型
{
    Chassis_data chassis_data;
    pthread_mutex_lock(&mick_lock);
    chassis_data.vx = vx;
    chassis_data.vy = vy;
    chassis_data.wz = wz;
    pthread_mutex_unlock(&mick_lock);
    return chassis_data;
}