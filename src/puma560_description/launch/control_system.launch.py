
from launch.actions import ExecuteProcess
from launch import LaunchDescription


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

    return LaunchDescription([
        load_joint_state_broadcaster,
        load_joint_effort_controller
    ])