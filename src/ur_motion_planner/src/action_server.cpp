#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <control_msgs/action/follow_joint_trajectory.hpp>
#include <trajectory_msgs/msg/joint_trajectory.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <algorithm>
#include <memory>
#include <thread>
#include <mutex>

using FollowJointTrajectory = control_msgs::action::FollowJointTrajectory;
using GoalHandle = rclcpp_action::ServerGoalHandle<FollowJointTrajectory>;

const std::string joint_name[] = {"shoulder_pan_joint",
                                  "shoulder_lift_joint",
                                  "elbow_joint",
                                  "wrist_1_joint",
                                  "wrist_2_joint",
                                  "wrist_3_joint"};
int joint_num[] = {-1, -1, -1, -1, -1, -1}; // Joint arr pos in the trajectory array

class MyTrajectoryActionServer : public rclcpp::Node
{
public:
  MyTrajectoryActionServer() : Node("my_trajectory_action_server")
  {
    
    action_server_ = rclcpp_action::create_server<FollowJointTrajectory>(
      this,
      "my_motion_planner",   // имя action
      std::bind(&MyTrajectoryActionServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
      std::bind(&MyTrajectoryActionServer::handle_cancel, this, std::placeholders::_1),
      std::bind(&MyTrajectoryActionServer::handle_accepted, this, std::placeholders::_1));

    // Создаём publisher в топик, который слушает система управления
    publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/desired/joint_positions", 10);
    // Create timer and immideately stop it
    timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10), std::bind(&MyTrajectoryActionServer::execute, this));
    timer_->cancel();

    RCLCPP_INFO(this->get_logger(), "Action server ready.");
  }

private:
    rclcpp_action::Server<FollowJointTrajectory>::SharedPtr action_server_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr command_pub_;

    rclcpp_action::GoalResponse handle_goal(
        const rclcpp_action::GoalUUID & uuid,
        std::shared_ptr<const FollowJointTrajectory::Goal> goal){

        (void)uuid;  // не используется
        
        RCLCPP_INFO(this->get_logger(), "Received goal request");
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse handle_cancel(
        const std::shared_ptr<GoalHandle> goal_handle){

        RCLCPP_INFO(this->get_logger(), "Received cancel request");
        // Здесь можно остановить выполнение траектории, если оно идёт
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    void handle_accepted(const std::shared_ptr<GoalHandle> goal_handle){

        goal_handle_ = goal_handle; // Save handler pointer
        const auto goal = goal_handle->get_goal();
        result_ = std::make_shared<FollowJointTrajectory::Result>();

        trajectory = std::make_shared<trajectory_msgs::msg::JointTrajectory>(goal->trajectory);

        if(trajectory->points.empty()){
            result_->error_code = FollowJointTrajectory::Result::INVALID_GOAL;
            goal_handle->abort(result_);
            return;
        }

        for(int i=0; i<6; i++){
            std::vector<std::__cxx11::basic_string<char>>::iterator it = std::find(trajectory->joint_names.begin(), trajectory->joint_names.end(), joint_name[i]);
            if(it != trajectory->joint_names.end()){
                joint_num[i] = std::distance(trajectory->joint_names.begin(), it);
            }
        }

        // Start from the beginning
        start_time = this->now();
        interp_index = 0;

        // Запускаем таймер
        timer_->reset();
    }

    void execute(void){
       
        rclcpp::Duration elapsed = this->now() - start_time;
        double t = elapsed.seconds(); // текущее время от начала траектории (сек)
        int arr_size = std::size(trajectory->points);

        while(interp_index < arr_size-1){
            rclcpp::Duration time_from_start_next(trajectory->points[interp_index+1].time_from_start);
            if(t < time_from_start_next.seconds()) break;

            interp_index ++;
        }

        // Создаем сообщение
        auto msg = std_msgs::msg::Float64MultiArray();
        msg.data.resize(12);

        if(interp_index == arr_size-1){
            for(int i=0; i<6; i++){
                msg.data[i] = trajectory->points[interp_index].positions[joint_num[i]];
                msg.data[i+6] = 0; // Stop at the end position
            }
            publisher_->publish(msg);

            // Если дошли сюда — траектория выполнена
            result_->error_code = FollowJointTrajectory::Result::SUCCESSFUL;
            goal_handle_->succeed(result_);
            // Stop timer
            timer_->cancel();
        }
        else{
            for(int i=0; i<6; i++){
                rclcpp::Duration time_next(trajectory->points[interp_index+1].time_from_start);
                rclcpp::Duration time_prev(trajectory->points[interp_index].time_from_start);
                double interval = time_next.seconds() - time_prev.seconds();
                double k = (t - time_prev.seconds())/interval;

                msg.data[i] = trajectory->points[interp_index].positions[joint_num[i]];
                msg.data[i] += (trajectory->points[interp_index+1].positions[joint_num[i]] -
                                trajectory->points[interp_index].positions[joint_num[i]])*k;

                msg.data[i+6] = trajectory->points[interp_index].velocities[joint_num[i]];
                msg.data[i+6] += (trajectory->points[interp_index+1].velocities[joint_num[i]] -
                                trajectory->points[interp_index].velocities[joint_num[i]])*k;
            }

            publisher_->publish(msg);
        }

    }

    int interp_index;
    rclcpp::Time start_time;
    trajectory_msgs::msg::JointTrajectory::SharedPtr trajectory;
    std::shared_ptr<GoalHandle> goal_handle_;
    std::shared_ptr<FollowJointTrajectory::Result> result_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_;
};



int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<MyTrajectoryActionServer>();
  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(node);
  executor.spin();
  rclcpp::shutdown();
  return 0;
}