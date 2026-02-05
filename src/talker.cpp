#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

// void on_timer() {
//   std_msgs::msg::String message;
//   // message.data = "Hello, world! " + std::to_string(this->count_++);
//   // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
//   // this->publisher_->publish(message);
// };

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    // timer_ = this->create_wall_timer(500ms, on_timer);
    timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::on_timer, this));
  }

private:
  void on_timer() {
    std_msgs::msg::String message;
    message.data = "Hello, world! " + std::to_string(this->count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    this->publisher_->publish(message);
  };

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}