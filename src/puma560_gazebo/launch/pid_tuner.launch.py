
from launch.actions import ExecuteProcess
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    pid_tuner = Node(
            package='puma560_gazebo',
            executable='pid_tuner',
            parameters=[{'use_sim_time': True}]
        )

    return LaunchDescription([
        pid_tuner
    ])