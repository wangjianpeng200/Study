#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <rclcpp/qos.hpp>

class QoSExampleNode : public rclcpp::Node
{
public:
    QoSExampleNode() : Node("qos_example_node")
    {
        // 创建一个自定义的QoS配置
        rclcpp::QoS qos_profile(10); // 队列深度为10
        qos_profile.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE); // 可靠性策略
        qos_profile.history(RMW_QOS_POLICY_HISTORY_KEEP_LAST); // 历史策略
        qos_profile.durability(RMW_QOS_POLICY_DURABILITY_VOLATILE); // 持久性策略

        // 使用QoS配置创建发布者
        publisher_ = create_publisher<std_msgs::msg::String>("qos_topic", qos_profile);

        // 使用相同的QoS配置创建订阅者
        subscription_ = create_subscription<std_msgs::msg::String>(
            "qos_topic", qos_profile,
            std::bind(&QoSExampleNode::topic_callback, this, std::placeholders::_1));

        // 定时器，用于发布消息
        timer_ = create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&QoSExampleNode::publish_message, this));
    }

private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received message: '%s'", msg->data.c_str());
    }

    void publish_message()
    {
        auto message = std_msgs::msg::String();
        message.data = "Hello, QoS! " + std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t count_ = 0;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<QoSExampleNode>());
    rclcpp::shutdown();
    return 0;
}