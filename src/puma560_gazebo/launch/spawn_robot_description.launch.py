
from launch_ros.actions import Node
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch.actions import OpaqueFunction

def launch_setup(context, *args, **kwargs):

    robot_name = LaunchConfiguration('robot_name').perform(context)
    x_spawn = LaunchConfiguration('x_spawn').perform(context)
    y_spawn = LaunchConfiguration('y_spawn').perform(context)

    position = [x_spawn, y_spawn, 0.0]
    orientation = [0.0, 0.0, 0.0]

    robot_description_topic_name = "/"+robot_name+"/robot_description"

    spawn_robot = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        name='spawn_entity',
        #namespace=robot_name,
        output='screen',
        arguments=['-entity', robot_name,
                   '-x', str(position[0]), '-y', str(position[1]), '-z', str(position[2]),
                   '-R', str(orientation[0]), '-P', str(orientation[1]), '-Y', str(orientation[2]),
                   '-topic', robot_description_topic_name]
    )

    return [
            spawn_robot
        ]

def generate_launch_description():

    robot_name_arg = DeclareLaunchArgument('robot_name', default_value='robot')
    x_spawn_arg = DeclareLaunchArgument('x_spawn', default_value='0.0')
    y_spawn_arg = DeclareLaunchArgument('y_spawn', default_value='0.0')

    return LaunchDescription([
        robot_name_arg,
        x_spawn_arg,
        y_spawn_arg, 
        OpaqueFunction(function = launch_setup)
        ])
