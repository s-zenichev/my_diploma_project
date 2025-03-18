#include "ui_pid_tuner.h"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include <cmath>
#include <chrono>

#include <QTimer>

using std::placeholders::_1;

Ui::MainWindow ui;
QTimer *timer = new QTimer();

class PidTuner : public rclcpp::Node
{
public:
    PidTuner(void) : Node("tuner"), count_(0)
    {      
        RCLCPP_INFO(get_logger(), "Node started!");
    }

    void publishPID()
    {
        if (pid_publisher_ != nullptr) pid_publisher_.reset();
        pid_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            ui.pidTopic->text().toStdString(), 10);

        auto message = std_msgs::msg::Float64MultiArray();

        message.data.resize(4);
        message.data[0] = ui.proportional->value();
        message.data[1] = ui.integral->value();
        message.data[2] = ui.derivative->value();
        message.data[3] = ui.filterConst->value();

        pid_publisher_->publish(message);
    }

    void publishControl()
    {
        if (control_publisher_ != nullptr) control_publisher_.reset();
        control_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            ui.controlTopic->text().toStdString(), 10);

        auto message = std_msgs::msg::Float64MultiArray();

        int joint = ui.jointNumber->value();
        message.data.resize(6);
        if(ui.radioButton->isChecked()) message.data[joint] = ui.firstValue->value();
        else message.data[joint] = ui.secondValue->value();

        control_publisher_->publish(message);
    }
private:
    
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr pid_publisher_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr control_publisher_;
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
    if (ui.autoPublish->isChecked()) node->publishControl();
 }

 void updateTimer(){
    timer->start(ui.switchTime->value());
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
    QObject::connect(timer, &QTimer::timeout, timerCallback);
    QObject::connect(ui.switchTime, &QSpinBox::textChanged, updateTimer);
    timer->start(ui.switchTime->value());
    window.show();
    app.exec();
    rclcpp::spin_some(node);
    node.reset();
    rclcpp::shutdown();
    return 0;
}
