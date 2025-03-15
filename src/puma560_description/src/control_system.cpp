#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include <cmath>
#include <chrono>

using std::placeholders::_1;

class ControlSystem : public rclcpp::Node
{
public:
    ControlSystem() : Node("control"), count_(0)
    {
      // Create the subscription.
      // The topic_callback function executes whenever data is published
      // to the 'addison' topic.
      subscription_ = this->create_subscription<sensor_msgs::msg::JointState>(
      "/joint_states", 10, std::bind(&ControlSystem::topic_callback, this, _1));
      
        publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/effort_controller/commands", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10000), std::bind(&ControlSystem::timer_callback, this));
    }

private:
    void timer_callback()
    {
        auto message = std_msgs::msg::Float64MultiArray();

        static int multiplyer = 1;
        message.data.resize(6);
        message.data[0] = 4 * multiplyer;
        multiplyer *= -1;

        publisher_->publish(message);
    }

    void topic_callback(const sensor_msgs::msg::JointState & msg)
    {
      float base_angle = msg.position[0];
      RCLCPP_INFO(this->get_logger(), "Base angle: '%f'", base_angle);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr subscription_; // Declare the subscription attribute
    size_t count_;
};


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ControlSystem>());
    rclcpp::shutdown();
    return 0;
}