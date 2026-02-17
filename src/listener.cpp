#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

//   void topic_callback(std_msgs::msg::String::UniquePtr msg)
//   {
//     // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
//   }

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = create_subscription<std_msgs::msg::String>(
      "topic", 10,
      std::bind(&MinimalSubscriber::topic_callback, this, std::placeholders::_1)
    );

    // subscription_ = this->create_subscription<std_msgs::msg::String>(
    //   "topic", 10, topic_callback);
  }

private:
  void topic_callback(std_msgs::msg::String::UniquePtr msg)
  {
    RCLCPP_INFO_STREAM(this->get_logger(), "I heard: " << msg->data);
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
