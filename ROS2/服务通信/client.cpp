#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>
#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

class AddTwoIntsClient : public rclcpp::Node
{
public:
    AddTwoIntsClient() : Node("add_two_ints_client")
    {
        // 创建客户端，连接到"add_two_ints"服务
        client_ = create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
    }

    // 发送请求的函数
    void send_request(int64_t a, int64_t b)
    {
        // 等待服务可用
        while (!client_->wait_for_service(1s)) 
        {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "客户端被中断，无法等待服务");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "等待服务可用...");
        }

        // 创建请求的消息类型
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;

        // 发送请求并处理响应
        auto result_future = client_->async_send_request(
            request,
            std::bind(&AddTwoIntsClient::response_callback, this, std::placeholders::_1));
    }

private:
    // 响应回调函数
    void response_callback(
        rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture future)
    {
        try {
            // 获取响应
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(), "响应结果: %ld + %ld = %ld",
                        request_a_, request_b_, response->sum);
        } catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "服务调用失败: %s", e.what());
        }
    }

    // 客户端对象指针
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;
    int64_t request_a_;
    int64_t request_b_;
};

int main(int argc, char * argv[])
{
    // 初始化ROS2
    rclcpp::init(argc, argv);

    // 创建客户端节点
    auto client = std::make_shared<AddTwoIntsClient>();

    // 检查命令行参数
    int64_t a = 0, b = 0;
    if (argc == 3) {
        a = std::stoll(argv[1]);
        b = std::stoll(argv[2]);
    } else {
        // 默认值
        a = 5;
        b = 3;
        RCLCPP_INFO(client->get_logger(), "使用默认参数: a = %ld, b = %ld", a, b);
    }

    // 发送请求
    client->send_request(a, b);

    // 运行节点直到完成
    rclcpp::spin(client);

    // 关闭ROS2
    rclcpp::shutdown();

    return 0;
}