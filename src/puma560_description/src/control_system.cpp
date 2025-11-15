#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "ament_index_cpp/get_package_share_directory.hpp"
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <cmath>
#include <string>
#include "config.h"
#include "robot_model.h"

//#define SPEED_TUNING

const std::string joint_name[] = {"shoulder_pan_joint",
                                  "shoulder_lift_joint",
                                  "elbow_joint",
                                  "wrist_1_joint",
                                  "wrist_2_joint",
                                  "wrist_3_joint"};
int joint_num[] = {0, 1, 2, 3, 4, 5};

std::string link_name[] = { "shoulder",
                            "upper_arm",
                            "forearm",
                            "wrist_1",
                            "wrist_2",
                            "wrist_3"};

const std::string links_config_path = ament_index_cpp::get_package_share_directory("ur_description")+
                "/config/ur15/physical_parameters.yaml";

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
        debug_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/puma560/debug", 10);
        vectors_ = this->create_publisher<visualization_msgs::msg::MarkerArray>(
            "/puma560/vectors", 10);

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10), std::bind(&ControlSystem::control_algorithm, this));

        tf_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

        initPID(speed_controller, position_controller, ament_index_cpp::get_package_share_directory("puma560_description")+
                "/config/pid_values.yaml");
        
        for(int i = 0; i<6; i++){
            links[i].read_config(link_name[i], links_config_path);
        }

        base_speed.setValue(0.0, 0.0, 0.0);
        base_acceleration.setValue(0.0, 0.0, 9.81);
        gripper_load.setValue(0.0, 0.0, 0.0);
        gripper_torque.setValue(0.0, 0.0, 0.0);
    }

private:
    void control_algorithm()
    {
        auto message = std_msgs::msg::Float64MultiArray();
        auto debug_message = std_msgs::msg::Float64MultiArray();
        message.data.resize(6);
        debug_message.data.resize(6);
        for (int i=0; i<6; i++)
        {
            double eps;
            #ifndef SPEED_TUNING
                eps = joint_desired_position[i] - joint_position[i];
                double _desired_speed = position_controller[i].control(eps);
                eps = _desired_speed - joint_speed[i];
            #else 
                eps = joint_desired_speed[i] - joint_speed[i];
            #endif
            debug_message.data[i] = speed_controller[i].getDerivative(eps);
            message.data[i] = speed_controller[i].control(eps);
        }

        publisher_->publish(message);
        debug_->publish(debug_message);

        // New algo testing below

        visualization_msgs::msg::MarkerArray marker_array;
        
        for(int i=0; i<6; i++){
            auto CoM = links[i].get_CoM();
            auto marker = create_vector_marker(6+i, links[i].get_name()+"_link", 0, 0, 0, CoM.x(), CoM.y(), CoM.z());
            marker_array.markers.push_back(marker);
        
            if (i!=5){
                if (tf_buffer_->canTransform(links[i].get_name()+"_link", 
                        links[i+1].get_name()+"_link", tf2::TimePointZero)){
                
                    geometry_msgs::msg::TransformStamped offsetTransform;
                    tf2::Transform transform;
                    tf2::Vector3 next_origin; 
                    tf2::Vector3 ri;

                    offsetTransform = tf_buffer_->lookupTransform(links[i].get_name()+"_link", 
                        links[i+1].get_name()+"_link", tf2::TimePointZero);
                    tf2::fromMsg(offsetTransform.transform, transform);
                    next_origin = transform.getOrigin();

                    ri = CoM - next_origin;
                    links[i].set_ri(ri);
                    
                    auto marker2 = create_vector_marker(i, links[i].get_name()+"_link", 
                        0, 0, 0, CoM.x()-ri.x(), CoM.y()-ri.y(), CoM.z()-ri.z());
                    marker_array.markers.push_back(marker2);
                }
            }
        }
        vectors_->publish(marker_array);

    }

    /// @brief Marker creation func
    /// @param id unique id
    /// @param x ass x coordinate
    /// @param y ass y coordinate 
    /// @param z ass z coordinate 
    /// @param tx tip x coordinate
    /// @param ty tip y coordinate 
    /// @param tz tip z coordinate 
    /// @param  
    /// @return 
    visualization_msgs::msg::Marker create_vector_marker(
    int id, std::string frame_id,
    double x, double y, double z, 
    double tx, double ty, double tz)
  {
    visualization_msgs::msg::Marker marker;
    marker.header.frame_id = frame_id;
    marker.header.stamp = this->now();
    marker.ns = "vector_array";
    marker.id = id; // УНИКАЛЬНЫЙ ID для каждого маркера!
    marker.type = visualization_msgs::msg::Marker::ARROW;
    marker.action = visualization_msgs::msg::Marker::ADD;
    
    geometry_msgs::msg::Point start, end;
    start.x = x;
    start.y = y;
    start.z = z;

    end.x = tx;
    end.y = ty;
    end.z = tz;

    marker.points.push_back(start);
    marker.points.push_back(end);
    
    marker.color.r = 1.0;
    marker.color.g = 0;
    marker.color.b = 0;
    marker.color.a = 1.0;

    marker.scale.x = 0.01; // толщина стрелки (диаметр вала)
    marker.scale.y = 0.02; // диаметр наконечника

    return marker;
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

    void pid_values_callback(const std_msgs::msg::Float64MultiArray & msg)
    {
        #ifdef SPEED_TUNING
            int joint_num = msg.data[0];
            speed_controller[joint_num].setP(msg.data[1]);
            speed_controller[joint_num].setI(msg.data[2]);
            speed_controller[joint_num].setD(msg.data[3]);
            speed_controller[joint_num].setN(msg.data[4]);
            speed_controller[joint_num].setIMin(msg.data[5]);
            speed_controller[joint_num].setIMax(msg.data[6]);
        #else
            int joint_num = msg.data[0];
            position_controller[joint_num].setP(msg.data[1]);
            position_controller[joint_num].setI(msg.data[2]);
            position_controller[joint_num].setD(msg.data[3]);
            position_controller[joint_num].setN(msg.data[4]);
            position_controller[joint_num].setIMin(msg.data[5]);
            position_controller[joint_num].setIMax(msg.data[6]);

        #endif
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
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr debug_;
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr vectors_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_states_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr pid_values_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr desired_joint_positions_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr desired_joint_speeds_;
    PID speed_controller[6];
    PID position_controller[6];
    LINK links[6];
    double joint_position[6];
    double joint_speed[6];
    double joint_desired_position[6];
    double joint_desired_speed[6];
    tf2::Vector3 base_speed;
    tf2::Vector3 base_acceleration;
    tf2::Vector3 gripper_load;
    tf2::Vector3 gripper_torque;
    std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
};


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ControlSystem>());
    rclcpp::shutdown();
    return 0;
}