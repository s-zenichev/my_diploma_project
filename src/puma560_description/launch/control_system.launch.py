
from launch.actions import ExecuteProcess
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    load_joint_state_broadcaster = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active',
            'joint_state_broadcaster'],
            output='screen'
    )

    load_joint_effort_controller = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active',
            'effort_controller'],
            output='screen'
    )

    custom_control = Node(
            package='puma560_description',
            executable='control_system',
            parameters=[{'use_sim_time': True}]
        )

    return LaunchDescription([
        load_joint_state_broadcaster,
        load_joint_effort_controller,
        custom_control
    ])