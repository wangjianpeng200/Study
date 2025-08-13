#include<Camera.h>

OpenCVCamera::OpenCVCamera(const std::string &device, int fps, int width, int height, int rotation)
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

cv::Mat OpenCVCamera::async_read() override
{
    cv::Mat frame, rotated;
    if (cap.read(frame))
    {
        cv::rotate(frame, rotated, static_cast<cv::RotateFlags>(rotation));
        return rotated;
    }
    return cv::Mat(); // 返回空矩阵表示失败
}