#include <chrono>
#include <memory>
#include <string>

#include "cpp_pubsub/msg/sphere.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std;
using namespace std::chrono_literals;


class MinimalPublisherSphere : public rclcpp::Node
{
public:
  MinimalPublisherSphere()
  : Node("minimal_publisher_sphere")
  {
    publisher_ = create_publisher<cpp_pubsub::msg::Sphere>("spheres", 10);
    timer_ = create_wall_timer(500ms, std::bind(&MinimalPublisherSphere::on_timer, this));
  }

private:
  void on_timer() {
    cpp_pubsub::msg::Sphere message;
    message.center.x = 0.0;
    message.center.y = 1.0;
    message.center.z = 2.0;
    message.radius = 10.0;
    RCLCPP_INFO_STREAM(
      this->get_logger(),
      "Publishing:"  << endl << 
      " message.center.x:"  << message.center.x << endl << 
      " message.center.y:"  << message.center.y << endl << 
      " message.center.z:"  << message.center.z << endl << 
      " message.radius:"  << message.radius << endl
    );
    this->publisher_->publish(message);
  };

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<cpp_pubsub::msg::Sphere>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisherSphere>());
  rclcpp::shutdown();
  return 0;
}