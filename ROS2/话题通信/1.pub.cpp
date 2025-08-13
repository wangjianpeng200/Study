#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class MinimalPublisher : public rclcpp::Node  //一个节点继承自Node
{
public:
  MinimalPublisher() : Node("minimal_publisher"), count_(0)   
  {
    // 创建发布者，话题名为"topic"，队列大小为10
    publisher_ = create_publisher<std_msgs::msg::String>("topic", 10);
    
    // 创建定时器，每500毫秒触发一次
    timer_ = create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    message.data = "Hello World: " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }
  
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());  //启动一个事件循环，持续监听和处理节点的回调函数，
  //如定时器
  rclcpp::shutdown();
  return 0;
}