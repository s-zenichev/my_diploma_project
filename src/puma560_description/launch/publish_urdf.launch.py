import os
import xacro
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch.actions import OpaqueFunction

# this is the function launch  system will look for
def launch_setup(context, *args, **kwargs):

    robot_name = LaunchConfiguration('robot_name').perform(context)
    pos_x = LaunchConfiguration('x_spawn').perform(context)
    pos_y = LaunchConfiguration('y_spawn').perform(context)
    joint_state_topic_name = robot_name + "_joint_states"
    robot_state_publisher_name = robot_name + "_robot_state_publisher"

    xacro_file = LaunchConfiguration('robot_file').perform(context)
    package_description = "puma560_description"

    print("Fetching XACRO ==>")
    robot_desc_path = os.path.join(get_package_share_directory(package_description), "xacro", xacro_file)
    robot_desc = xacro.process_file(robot_desc_path, mappings={'robot_name' : robot_name, 'pos_x': pos_x, 'pos_y': pos_y})

    xml = robot_desc.toxml()
    
    # Robot State Publisher

    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        namespace=robot_name,
        name=robot_state_publisher_name,
        emulate_tty=True,
        parameters=[{'use_sim_time': True,
                     'robot_description': xml}],
        remappings=[("/joint_states", joint_state_topic_name),
                    ("/tf", robot_name+"_tf"),
                    ("/tf_static", robot_name+"_tf_static")],
        output="screen"
    )


    if robot_name == 'puma0':
        # RVIZ Configuration
        rviz_config_dir = os.path.join(get_package_share_directory(package_description), 'rviz', 'puma560_rviz.rviz')


        rviz_node = Node(
                package='rviz2',
                executable='rviz2',
                output='screen',
                name='rviz_node',
                parameters=[{'use_sim_time': True}],
                arguments=['-d', rviz_config_dir])

        # create and return launch description object
        return [           
                robot_state_publisher_node,
                rviz_node
                ]
    else:
        return [robot_state_publisher_node]

def generate_launch_description():

    robot_name_arg = DeclareLaunchArgument('robot_name', default_value='puma560_default')
    pos_x = DeclareLaunchArgument('x_spawn', default_value='0.0')
    pos_y = DeclareLaunchArgument('y_spawn', default_value='0.0')
    urdf_file_arg = DeclareLaunchArgument('robot_file', default_value='puma560_robot.urdf')

    return LaunchDescription([
        robot_name_arg,
        pos_x,
        pos_y,
        urdf_file_arg,
        OpaqueFunction(function = launch_setup)
        ])
