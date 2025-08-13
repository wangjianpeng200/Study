#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>

class AddTwoIntsServer : public rclcpp::Node
{
public:
    AddTwoIntsServer() : Node("add_two_ints_server")
    {
        // 创建服务，服务名为"add_two_ints"，回调函数为handle_add_two_ints
        service_ = create_service<example_interfaces::srv::AddTwoInts>(
            "add_two_ints",
            std::bind(&AddTwoIntsServer::handle_add_two_ints, this,
                      std::placeholders::_1, std::placeholders::_2));

        RCLCPP_INFO(this->get_logger(), "服务端已启动，等待客户端请求...");
    }

private:
    // 服务回调函数
    void handle_add_two_ints(
        const example_interfaces::srv::AddTwoInts::Request::SharedPtr request,
        example_interfaces::srv::AddTwoInts::Response::SharedPtr response)
    {
        // 计算两个整数的和
        response->sum = request->a + request->b;

        // 打印请求和响应信息
        RCLCPP_INFO(this->get_logger(), "接收到请求: a = %ld, b = %ld",
                    request->a, request->b);
        RCLCPP_INFO(this->get_logger(), "发送响应: sum = %ld", response->sum);
    }

    // 服务对象指针
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service_;
};

int main(int argc, char * argv[])
{
    // 初始化ROS2
    rclcpp::init(argc, argv);

    // 运行服务端节点
    rclcpp::spin(std::make_shared<AddTwoIntsServer>());

    // 关闭ROS2
    rclcpp::shutdown();

    return 0;
}