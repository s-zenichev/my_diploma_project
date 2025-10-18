
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "ament_index_cpp/get_package_share_directory.hpp"
#include <cmath>
#include <chrono>
#include <string>
#include <iostream>

#include <psocpp.h>

#define SPEED_TUNING

const std::string joint_name[] = {"platform", "shoulder", "elbow", "wrist_revolute", "wrist_bend", "effector_revolute"};
int joint_num[] = {0, 1, 2, 3, 4, 5};

double desired_speed = 0.2;
double desired_position = 1.0;

using std::placeholders::_1;

class StepResponse : public rclcpp::Node
{
public:
    StepResponse() : Node("step_response")
    {
        joint_states_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "/joint_states", 10, std::bind(&StepResponse::joint_topic_callback, this, _1));   
        desired_joint_positions_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/desired/joint_positions", 10);
        desired_joint_speeds_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/desired/joint_speeds", 10);
        pid_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/pid_values", 10);
        debug_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/puma560/debug", 10);
        
        
    }

    void resetRobot(){
        if (reset_ == nullptr)
            reset_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
                "/set_joint_states", 10);
                
        auto message = std_msgs::msg::Float64MultiArray();
        message.data.resize(12);
        for (int i=0; i<12; i++) message.data[i] = 0.0;
        reset_->publish(message);

        message.data.resize(6);
        #ifdef SPEED_TUNING
            for (int i=0; i<6; i++) message.data[i] = desired_speed;
            desired_joint_speeds_->publish(message);
        #else
        for (int i=0; i<6; i++) message.data[i] = desired_position;
            desired_joint_positions_->publish(message);
        #endif
    }

    template<typename Derived>
    double opt(const Eigen::MatrixBase<Derived> &xval)
    {
        optimization_running = true;
        time_set = false;
        resetRobot();
        while (time < 2){
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if(!rclcpp::ok()) return(0);
        }
        optimization_running = false;
        return integrator;
    }
private:


    bool joints_enumerated(const sensor_msgs::msg::JointState & msg){
        bool joints_enumerated = true;
        for (int i = 0; i<6; i++)
            if (msg.name[i] != joint_name[joint_num[i]])
                joints_enumerated = false;
        return joints_enumerated;
    }

    void joint_topic_callback(const sensor_msgs::msg::JointState & msg)
    {
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
        if (optimization_running && (desired_positions_set || desired_speeds_set)){
            if (!time_set){
                initial_time = msg.header.stamp;
                prev_time =  msg.header.stamp;
                integrator = 0;
                time_set = true;
                for (int i=0; i<6; i++) prev_error[i] = 0;
            }
            else{
                rclcpp::Duration duration = msg.header.stamp - initial_time;
                rclcpp::Duration time_step = msg.header.stamp - prev_time;
                time = duration.seconds();
            
                for (int i=0; i<6; i++){
                    #ifdef SPEED_TUNING
                        error[i] = desired_speed - joint_speed[i];
                        if (error[i] < -desired_speed*0.1) integrator = 1e10;
                    #else
                        error[i] = desired_position - joint_position[i];
                    #endif
                    integrator += pow((error[i]+prev_error[i])/2*time_step.seconds(), 2);
                    prev_error[i] = error[i];
                }
                
                prev_time = msg.header.stamp;
            }
        }
    }


    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr pid_publisher_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr debug_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr reset_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr desired_joint_positions_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr desired_joint_speeds_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_states_;
    double joint_position[6];
    double joint_speed[6];
    double error[6];
    double prev_error[6];
    rclcpp::Time initial_time;
    rclcpp::Time prev_time;
    double integrator;
    double time = 0.0;
    bool optimization_running = false;
    bool time_set = false;
};


auto shutdown_flag = std::make_shared<std::atomic<bool>>(false);

void signal_handler(int) {
    *shutdown_flag = true;
}

std::shared_ptr<StepResponse> step_response;

struct Wrap
{
    template<typename Derived>
    double operator()(const Eigen::MatrixBase<Derived> &xval) const
    {
        return step_response->opt(xval);
    }
};


int main(int argc, char * argv[])
{
    // Установка обработчика сигнала
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    rclcpp::InitOptions init_options;
    // Отключаем обработку SIGINT (Ctrl+C) ROS 2
    init_options.shutdown_on_signal = false;
    // Инициализируем ROS с указанными параметрами
    rclcpp::init(argc, argv, init_options);

    step_response = std::make_shared<StepResponse>();
    std::thread ros_thread([](){
        rclcpp::spin(step_response);
    });
    pso::ParticleSwarmOptimization<double, Wrap> optimizer;
    optimizer.setMaxIterations(100);
    optimizer.setMinParticleChange(1e-6);
    optimizer.setMinFunctionChange(1e-6);
    optimizer.setThreads(1);
    optimizer.setVerbosity(2);
    Eigen::MatrixXd bounds(2, 1);
    bounds <<   -2, 
                2;
    auto result = optimizer.minimize(bounds, 50, shutdown_flag);

    std::cout << "Done! Converged: " << (result.converged ? "true" : "false")
        << " Iterations: " << result.iterations << std::endl;

    // do something with final function value
    std::cout << "Final fval: " << result.fval << std::endl;

    // do something with final x-value
    std::cout << "Final xval: " << result.xval.transpose() << std::endl;

    rclcpp::shutdown();
    if (ros_thread.joinable()) ros_thread.join();
    return 0;
}
