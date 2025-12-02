#include "ui_pid_tuner.h"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include <cmath>
#include <chrono>

#include <QTimer>

using std::placeholders::_1;

Ui::MainWindow ui;
QTimer *timer = new QTimer();
QTimer *timer2 = new QTimer();
bool pid_topic_changed = true;
bool control_topic_changed = true;

class PidTuner : public rclcpp::Node
{
public:
    PidTuner(void) : Node("tuner"), count_(0)
    {   
        control_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
                "/desired/joint_positions", 10);
        control_publisher_2_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
                "/desired/joint_speeds", 10);
        pid_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
                "/pid_values", 10);   
        RCLCPP_INFO(get_logger(), "Node started!");
    }

    void publishPID()
    {
        auto message = std_msgs::msg::Float64MultiArray();

        message.data.resize(8);
        message.data[0] = ui.pidPosition->isChecked();
        message.data[1] = ui.pidJointNumber->value();
        message.data[2] = ui.proportional->value();
        message.data[3] = ui.integral->value();
        message.data[4] = ui.derivative->value();
        message.data[5] = ui.filterConst->value();
        message.data[6] = ui.integrator_min->value();
        message.data[7] = ui.integrator_max->value();

        pid_publisher_->publish(message);
    }

    void publishControl()
    {
        auto message = std_msgs::msg::Float64MultiArray();

        message.data.resize(12);
        for(int i = 0; i<6; i++) message.data[i] = 0.0; //-0.2;
        if(ui.radioButton->isChecked()) message.data[joint] = ui.firstValue->value();
        else message.data[joint] = ui.secondValue->value();

        int joint = ui.jointNumber->value();
        control_publisher_->publish(message);
    }

    void resetRobot(){

        if (robot_position_publisher_ == nullptr)
            robot_position_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
                "/set_joint_states", 10);
                
        auto message = std_msgs::msg::Float64MultiArray();
        message.data.resize(12);
        
        for (int i=0; i<12; i++) message.data[i] = 0.0;

        robot_position_publisher_->publish(message);
    }

private:
    
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr pid_publisher_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr control_publisher_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr robot_position_publisher_;
    size_t count_;
};


std::shared_ptr<PidTuner> node;

void pubPID(){
    node->publishPID();

 }

 void pubControl(){
    node->publishControl();

 }


 void timerCallback(){
    if (ui.autoSwitch->isChecked()){
        if(ui.radioButton->isChecked()) ui.radioButton_2->click();
        else ui.radioButton->click();
    }
 }

 void timer2Callback(){
    if (ui.autoPublish->isChecked()) node->publishControl();
 }

 void updateTimer(){
    timer->start(ui.switchTime->value());
 }


 void reset_robot(){
    node->resetRobot();
 }


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    node = std::shared_ptr<PidTuner>(new PidTuner);
    QApplication app(argc, argv);
    QMainWindow window;
    ui.setupUi(&window);
    QObject::connect(ui.publishPID, &QPushButton::released, pubPID);
    QObject::connect(ui.publishControl, &QPushButton::released, pubControl);
    QObject::connect(ui.resetButton, &QPushButton::released, reset_robot);
    QObject::connect(timer, &QTimer::timeout, timerCallback);
    QObject::connect(timer2, &QTimer::timeout, timer2Callback);
    QObject::connect(ui.switchTime, &QSpinBox::textChanged, updateTimer);
    timer->start(ui.switchTime->value());
    timer2->start(10);
    window.show();
    app.exec();
    rclcpp::spin_some(node);
    node.reset();
    rclcpp::shutdown();
    return 0;
}
