#include<unility.h>
#include<opencv2/opencv.hpp>

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