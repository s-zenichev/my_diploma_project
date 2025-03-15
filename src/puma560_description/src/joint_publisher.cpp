#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include <cmath>
#include <chrono>

class JointPublisher : public rclcpp::Node
{
public:
    JointPublisher() : Node("joint_publisher"), count_(0){
        publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/effort_controller/commands", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10000), std::bind(&JointPublisher::timer_callback, this));
    }

private:
    void timer_callback(){
        auto message = std_msgs::msg::Float64MultiArray();

        static int multiplyer = 1;
        message.data.resize(6);
        message.data[0] = 4 * multiplyer;
        multiplyer *= -1;

        publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JointPublisher>());
    rclcpp::shutdown();
    return 0;
}