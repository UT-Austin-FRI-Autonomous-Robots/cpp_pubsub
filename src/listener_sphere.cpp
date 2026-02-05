#include <memory>

#include "cpp_pubsub/msg/sphere.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std;

class MinimalSubscriberSphere : public rclcpp::Node
{
public:
  MinimalSubscriberSphere()
  : Node("minimal_subscriber_sphere")
  {
    subscription_ = this->create_subscription<cpp_pubsub::msg::Sphere>(
      "spheres", 10,
      std::bind(&MinimalSubscriberSphere::topic_callback, this, std::placeholders::_1)
    );
  }

private:
  void topic_callback(cpp_pubsub::msg::Sphere::UniquePtr msg)
  {

    RCLCPP_INFO_STREAM(
      this->get_logger(),
      "Publishing:"  << endl << 
      " message.center.x:"  << msg->center.x << endl << 
      " message.center.y:"  << msg->center.y << endl << 
      " message.center.z:"  << msg->center.z << endl << 
      " message.radius:"  << msg->radius << endl
    );
  }

  rclcpp::Subscription<cpp_pubsub::msg::Sphere>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriberSphere>());
  rclcpp::shutdown();
  return 0;
}
