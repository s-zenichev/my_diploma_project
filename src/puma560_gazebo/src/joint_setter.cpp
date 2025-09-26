
#include <gazebo-11/gazebo/gazebo.hh>
#include <gazebo-11/gazebo/physics/physics.hh>
#include <gazebo-11/gazebo/common/common.hh>
#include <gazebo-11/gazebo/common/Plugin.hh>
#include <gazebo_ros/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <string.h>
#include <stdio.h>

namespace gazebo
{
  class JointSetterPlugin : public ModelPlugin
  {
  public:
    void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) override
    {
      //ros_node_ = gazebo_ros::Node::Get(_sdf);
      node_ = gazebo_ros::Node::Get(_sdf);
      RCLCPP_INFO(rclcpp::get_logger("joint_setter_plugin"), "Plugin started!");

      model_ = _model;
      if (model_ != nullptr) RCLCPP_INFO(rclcpp::get_logger("joint_setter_plugin"), "Model ptr loaded!");
      if(_sdf->HasElement("robot_name")){
        std::string robot_name = _sdf->Get<std::string>("robot_name");
        for (int i=0; i<7; i++) joint_names_[i] = robot_name + "_" + joint_names_[i];
        std::cout<<joint_names_[1]<<std::endl;
      }

      RCLCPP_INFO(rclcpp::get_logger("joint_setter_plugin"), "Node created!");
      sub_ = node_->create_subscription<std_msgs::msg::Float64MultiArray>(
        "/set_joint_states", 10,
        std::bind(&JointSetterPlugin::OnJointStatesMsg, this, std::placeholders::_1));
      
      if (sub_ != nullptr) RCLCPP_INFO(rclcpp::get_logger("joint_setter_plugin"), "Subscription created!");
      else RCLCPP_INFO(rclcpp::get_logger("joint_setter_plugin"), "Failed to subscribe!");
      // Запуск спиннниг ROS2 в отдельном потоке
      thread_ = std::thread([this]()
      {
        rclcpp::spin(node_);
      });
    }

    void OnJointStatesMsg(const std_msgs::msg::Float64MultiArray::SharedPtr msg)
    {
      RCLCPP_INFO(rclcpp::get_logger("joint_setter_plugin"), "Msg received!");
      // Пример: msg->data = [angle1, vel1, angle2, vel2, ...]
      for(size_t i = 0; i < joint_names_.size() && i*2+1 < msg->data.size(); ++i)
      {
        auto joint = model_->GetJoint(joint_names_[i]);
        if(joint)
        {
          joint->SetPosition(0, msg->data[i*2]);
          joint->SetVelocity(0, msg->data[i*2+1]);
        }
      }
    }

  private:
    physics::ModelPtr model_;
    rclcpp::Node::SharedPtr node_;
    gazebo_ros::Node::SharedPtr ros_node_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr sub_;
    std::thread thread_;

    // Нужно заполнить по вашим именам суставов
    std::vector<std::string> joint_names_ = 
    {"platform", "shoulder", "elbow", "wrist_revolute", "wrist_bend", "effector_revolute"};
  };

  // Регистрация плагина
  GZ_REGISTER_MODEL_PLUGIN(JointSetterPlugin)
}
