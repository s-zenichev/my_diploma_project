
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include <cmath>
#include <chrono>

// Filter time constant, ms
#define TIME_CONST 3.0

#define SIGN(x) ((x) < 0 ? -1 : 1)
#define NO_FRICTION

using std::placeholders::_1;

const std::string joint_name[] = {"shoulder_pan_joint",
                                  "shoulder_lift_joint",
                                  "elbow_joint",
                                  "wrist_1_joint",
                                  "wrist_2_joint",
                                  "wrist_3_joint"};
int joint_num[] = {0, 1, 2, 3, 4, 5};

// Friction parameters
double T_brk[] = {3.0, 3.0, 3.0, 0.56, 0.56, 0.56};
double T_c[] = {0.0225, 0.0225, 0.0225, 0.0028, 0.0028, 0.0028};
double omega_th[] = {0.03, 0.03, 0.03, 0.02, 0.02, 0.02};
double C[] = {1.5, 1.5, 1.5, 2, 2, 2};
double Fr[] = {0.005, 0.005, 0.005, 0.001, 0.001, 0.001}; 

class DummyMotor : public rclcpp::Node
{
public:
    DummyMotor(void) : Node("motor_driver")
    {   
        period = 1.0; // ms

        joint_states_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "/joint_states", 10, std::bind(&DummyMotor::joint_topic_callback, this, _1)); 
        desired_torque_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/motor_driver/torque", 10, std::bind(&DummyMotor::torque_callback, this, _1));
        torque_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/effort_controller/commands", 10);
        
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1), std::bind(&DummyMotor::publish_torque, this));
        
        alpha = 1; //std::exp(-TIME_CONST/period);
        RCLCPP_INFO(get_logger(), "Motor started!");
    }

    void torque_callback(const std_msgs::msg::Float64MultiArray & msg){
        for(int i=0; i<6; i++){
            desired_torque[i] = msg.data[i];
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
            joint_speed[joint_num[i]] = msg.velocity[i];
        }
    }

    void publish_torque(void){

        auto message = std_msgs::msg::Float64MultiArray();
        message.data.resize(6);

        for(int i=0; i<6; i++){
            torque[i] += alpha * (desired_torque[i] - torque[i]);
            #ifdef NO_FRICTION
                message.data[i] = torque[i];
            #else
                if(abs(joint_speed[i]) <= omega_th[i]){
                    message.data[i] = torque[i] - T_brk[i]*joint_speed[i]/omega_th[i];
                }
                else{
                    message.data[i] = torque[i] - SIGN(joint_speed[i])*(T_c[i] + (T_brk[i] - T_c[i])*exp(-C[i]*(abs(joint_speed[i])-omega_th[i])) + Fr[i]*(abs(joint_speed[i])-omega_th[i]));
                }
            #endif
        }

        torque_publisher_->publish(message);
    }

private:
    
    double alpha;
    double period;
    double desired_torque[6] = {0,};
    double torque[6] = {0,};
    double joint_speed[6] = {0,};
    rclcpp::TimerBase::SharedPtr timer_; 
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr torque_publisher_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr desired_torque_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_states_;
    
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DummyMotor>());
    rclcpp::shutdown();
    return 0;
}
