import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.substitutions import Command
from launch_ros.actions import Node

def generate_launch_description():

    robot_description_path = os.path.join(get_package_share_directory("puma560_description"),"/urdf/puma560_robot.urdf")

    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher_node",
        emulate_tty=True,
        parameters=[{'use_sim_time':True, 'robot_description': Command(['xacro', robot_description_path])}],
        output='screen'
    )

    return LaunchDescription(
        robot_state_publisher_node
    ) 