
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "ament_index_cpp/get_package_share_directory.hpp"
#include <cmath>
#include <chrono>
#include <string>
#include <iostream>

#include <psocpp.h>

#define TIME_STEP 1

const std::string joint_name[] = {"platform", "shoulder", "elbow", "wrist_revolute", "wrist_bend", "effector_revolute"};
int joint_num[] = {0, 1, 2, 3, 4, 5};

using std::placeholders::_1;

class StepResponse : public rclcpp::Node
{
public:
    StepResponse() : Node("step_response")
    {
        joint_states_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "/joint_states", 10, std::bind(&StepResponse::joint_topic_callback, this, _1));   
        desired_joint_positions_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/desired/joint_positions", 10, std::bind(&StepResponse::desired_positions_callback, this, _1));
        desired_joint_speeds_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/desired/joint_speeds", 10, std::bind(&StepResponse::desired_speeds_callback, this, _1));
        debug_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/puma560/debug", 10);

        this->reset_timer();
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(TIME_STEP), std::bind(&StepResponse::timer, this));
        
        
    }

    template<typename Derived>
    double opt(const Eigen::MatrixBase<Derived> &xval)
    {
        if(!rclcpp::ok()) return(0);
        this->reset_timer();
        while (time < 50)std::this_thread::sleep_for(std::chrono::milliseconds(1));
        return abs(xval(0));
    }
    void stop() {
        // Остановка всех внутренних процессов
        timer_->cancel();
    }

private:

    void timer(){
        time += TIME_STEP;
    }

    void reset_timer(){
        time = 0;
    }

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
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr debug_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_states_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr desired_joint_positions_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr desired_joint_speeds_;
    double joint_position[6];
    double joint_speed[6];
    double joint_desired_position[6];
    double joint_desired_speed[6];
    double time;
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

    step_response->stop();
    rclcpp::shutdown();
    if (ros_thread.joinable()) ros_thread.join();
    return 0;
}
