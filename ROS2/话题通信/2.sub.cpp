#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber(): Node("minimal_subscriber")
  {
    // 创建订阅者，订阅"topic"话题，队列大小为10
    subscription_ = create_subscription<std_msgs::msg::String>(
      "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, std::placeholders::_1));
  }

private:
  void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
  }
  
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}