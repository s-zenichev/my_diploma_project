
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include <cmath>
#include <chrono>
#include <fstream>

using std::placeholders::_1;

const std::string joint_name[] = {"shoulder_pan_joint",
                                  "shoulder_lift_joint",
                                  "elbow_joint",
                                  "wrist_1_joint",
                                  "wrist_2_joint",
                                  "wrist_3_joint"};
int joint_num[] = {0, 1, 2, 3, 4, 5};

std::ofstream outFile;


class DataLogger : public rclcpp::Node
{
public:
    DataLogger(void) : Node("data_logger")
    {   

        joint_states_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "/joint_states", 10, std::bind(&DataLogger::joint_topic_callback, this, _1)); 
        desired_torque_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/motor_driver/torque", 10, std::bind(&DataLogger::torque_callback, this, _1));
        real_torque_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/effort_controller/commands", 10, std::bind(&DataLogger::real_torque_callback, this, _1));
        desired_position_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/desired/joint_positions", 10, std::bind(&DataLogger::desired_positions_callback, this, _1));
        desired_speed_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/desired/joint_speeds", 10, std::bind(&DataLogger::desired_speeds_callback, this, _1));
        
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1), std::bind(&DataLogger::data_write, this));
        
        RCLCPP_INFO(get_logger(), "Logger started!");
    }

    void data_write(){
        outFile << time << ", ";
        for(int i=0; i<6; i++) outFile << joint_position[i] << ", ";
        for(int i=0; i<6; i++) outFile << joint_speed[i] << ", ";
        for(int i=0; i<6; i++) outFile << desired_position[i] << ", ";
        for(int i=0; i<6; i++) outFile << desired_speed[i] << ", ";
        for(int i=0; i<6; i++) outFile << desired_torque[i] << ", ";
        for(int i=0; i<5; i++) outFile << torque[i] << ", ";
        outFile << torque[5] << std::endl;

        time++;
    }

    void torque_callback(const std_msgs::msg::Float64MultiArray & msg){
        for(int i=0; i<6; i++){
            desired_torque[i] = msg.data[i];
        }
    }

    void real_torque_callback(const std_msgs::msg::Float64MultiArray & msg){
        for(int i=0; i<6; i++){
            torque[i] = msg.data[i];
        }
    }

    bool joints_enumerated(const sensor_msgs::msg::JointState & msg){
        bool joints_enumerated = true;
        for (int i = 0; i<6; i++)
            if (msg.name[i] != joint_name[joint_num[i]])
                joints_enumerated = false;
        return joints_enumerated;
    }

    void joint_topic_callback(const sensor_msgs::msg::JointState & msg){
        if (!joints_enumerated(msg)){
            for(int i = 0; i<6; i++){
                for(int u = 0; u<6; u++){
                    if (msg.name[i] == joint_name[u])joint_num[i] = u;  
                }
            }
        }
        for (int i=0; i<6; i++)
        {
            joint_position[joint_num[i]] = msg.position[i];
            joint_speed[joint_num[i]] = msg.velocity[i];
        }
    }

     void desired_positions_callback(const std_msgs::msg::Float64MultiArray & msg)
    {
        for (int i=0; i<6; i++)
        {
            desired_position[i] = msg.data[i];
            if(msg.data.size() == 12) desired_speed[i] = msg.data[i+6];
        }
    }
    void desired_speeds_callback(const std_msgs::msg::Float64MultiArray & msg)
    {
        for (int i=0; i<6; i++)
        {
            desired_speed[i] = msg.data[i];
        }
    }

private:
    int time = 0;
    double alpha;
    double period;
    double desired_torque[6] = {0,};
    double desired_position[6] = {0,};
    double desired_speed[6] = {0,};
    double torque[6] = {0,};
    double joint_position[6] = {0,};
    double joint_speed[6] = {0,};
    rclcpp::TimerBase::SharedPtr timer_; 
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr desired_torque_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr real_torque_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_states_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr desired_position_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr desired_speed_;
    
};

int main(int argc, char * argv[])
{
    outFile = std::ofstream(argv[1]);
    if(outFile.is_open()){
        std::cout << "File open" << std::endl;
        outFile << "timestamp, joint_positions[], joint_speeds[], desired_position[], desired_speed[], desired_torque[], real_torque[]" << std::endl;
        rclcpp::init(argc, argv);
        rclcpp::spin(std::make_shared<DataLogger>());
        rclcpp::shutdown();
        outFile.close();
        std::cout << "File closed" << std::endl;
    }
    else{
        std::cout << "Could not open file" << std::endl;
    }
    return 0;
}
