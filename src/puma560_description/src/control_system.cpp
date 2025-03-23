#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "ament_index_cpp/get_package_share_directory.hpp"
#include <cmath>
#include <chrono>

#include "pid.h"
#include "config.h"

using std::placeholders::_1;

class ControlSystem : public rclcpp::Node
{
public:
    ControlSystem() : Node("control")
    {
        joint_states_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "/joint_states", 10, std::bind(&ControlSystem::joint_topic_callback, this, _1));
        pid_values_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/pid_values", 10, std::bind(&ControlSystem::pid_values_callback, this, _1));
        desired_joint_positions_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/desired/joint_positions", 10, std::bind(&ControlSystem::desired_positions_callback, this, _1));
        desired_joint_speeds_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/desired/joint_speeds", 10, std::bind(&ControlSystem::desired_speeds_callback, this, _1));
      
        publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/effort_controller/commands", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10), std::bind(&ControlSystem::control_algorithm, this));

        initPID(speed_controller, position_controller, ament_index_cpp::get_package_share_directory("puma560_description")+
                "/config/pid_values.yaml");
        
    }

private:
    void control_algorithm()
    {
        auto message = std_msgs::msg::Float64MultiArray();
        message.data.resize(6);
        for (int i=0; i<6; i++)
        {
            double eps = joint_desired_speed[i] - joint_speed[i];
            message.data[i] = speed_controller[i].control(eps);
        }

        publisher_->publish(message);
    }

    void joint_topic_callback(const sensor_msgs::msg::JointState & msg)
    {
        for (int i=0; i<6; i++)
        {
            joint_position[i] = msg.position[i];
            joint_speed[i] = msg.velocity[i];
        }
    }

    void pid_values_callback(const std_msgs::msg::Float64MultiArray & msg)
    {
        int joint_num = msg.data[0];
        speed_controller[joint_num].setP(msg.data[1]);
        speed_controller[joint_num].setI(msg.data[2]);
        speed_controller[joint_num].setD(msg.data[3]);
        speed_controller[joint_num].setN(msg.data[4]);
    }
    void desired_positions_callback(const std_msgs::msg::Float64MultiArray & msg)
    {
        for (int i=0; i<6; i++)
        {
            joint_desired_position[i] = msg.data[i];
        }
    }
    void desired_speeds_callback(const std_msgs::msg::Float64MultiArray & msg)
    {
        for (int i=0; i<6; i++)
        {
            joint_desired_speed[i] = msg.data[i];
        }
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_states_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr pid_values_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr desired_joint_positions_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr desired_joint_speeds_;
    PID speed_controller[6];
    PID position_controller[6];
    double joint_position[6];
    double joint_speed[6];
    double joint_desired_position[6];
    double joint_desired_speed[6];
};


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ControlSystem>());
    rclcpp::shutdown();
    return 0;
}