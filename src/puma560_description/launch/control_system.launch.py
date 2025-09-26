

from launch_ros.actions import Node
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch.actions import OpaqueFunction


def launch_setup(context, *args, **kwargs):

    robot_name = LaunchConfiguration('robot_name').perform(context)

    joint_broadcaster_name = robot_name+"_joint_state_broadcaster"
    effort_controller_name = robot_name+"_effort_controller"
    controller_manager_name = robot_name+"_controller_manager"

    joint_state_topic_name = robot_name+"_joint_states"

    joint_broadcaster = Node(
        package="controller_manager",
        executable="spawner",
        name=joint_broadcaster_name,
        namespace=robot_name,
        arguments=["joint_state_broadcaster", "--controller-manager", controller_manager_name],
        remappings=[("/joint_states", joint_state_topic_name)],
        output="screen"
    )

    effort_controller = Node(
        package="controller_manager",
        executable="spawner",
        name=effort_controller_name,
        namespace=robot_name,
        arguments=["effort_controller", "--controller-manager", controller_manager_name],
        output="screen"
    )

    return [
        joint_broadcaster,
        effort_controller
    ]

def generate_launch_description():

    robot_name_arg = DeclareLaunchArgument('robot_name', default_value='puma_default')

    return LaunchDescription([
        robot_name_arg,
        OpaqueFunction(function=launch_setup)
    ])