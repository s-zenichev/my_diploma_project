#include "ui_pid_tuner.h"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include <cmath>
#include <chrono>

using std::placeholders::_1;


class PidTuner : public rclcpp::Node
{
public:
    PidTuner(void) : Node("tuner"), count_(0)
    {      
        publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/effort_controller/commands", 10);
        RCLCPP_INFO(get_logger(), "Node started!");
    }

    void timer_callback()
    {
        auto message = std_msgs::msg::Float64MultiArray();

        static int multiplyer = 1;
        message.data.resize(1);
        message.data[0] = 4 * multiplyer;
        multiplyer *= -1;

        publisher_->publish(message);
    }
private:
    
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_;
    size_t count_;
};


std::shared_ptr<PidTuner> node;

void func(){
    node->timer_callback();

 }

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    node = std::shared_ptr<PidTuner>(new PidTuner);
    QApplication app(argc, argv);
    QMainWindow window;
    Ui::MainWindow ui;
    ui.setupUi(&window);
    QObject::connect(ui.publishPID, &QPushButton::released, func);
    window.show();
    app.exec();
    //rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
