cmake_minimum_required(VERSION 3.8)
project(puma560_gazebo)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(puma560_description REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(gazebo_dev REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(gazebo REQUIRED)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

set (PROJECT_SOURCES
    include/ui_pid_tuner.h
    src/pid_tuner.cpp)

add_library(joint_setter_plugin SHARED
  src/joint_setter.cpp
)

# Линковка с необходимыми библиотеками
target_include_directories(joint_setter_plugin PRIVATE
  ${rclcpp_INCLUDE_DIRS}
  ${std_msgs_INCLUDE_DIRS}
  ${gazebo_INCLUDE_DIRS}
)

ament_target_dependencies(joint_setter_plugin
  rclcpp
  std_msgs
  gazebo
  gazebo_ros
)

target_link_libraries(joint_setter_plugin
  ${gazebo_LIBRARIES}
)

# Устанавливаем shared library в правильное место (обычно lib/ros2)
install(TARGETS joint_setter_plugin
  LIBRARY DESTINATION lib
)

# Добавляем поддержку установки файлов плагина, если надо
#ament_package()

add_executable(pid_tuner ${PROJECT_SOURCES})
target_include_directories(pid_tuner PRIVATE include)
target_link_libraries(pid_tuner Qt5::Widgets)
ament_target_dependencies(pid_tuner rclcpp std_msgs)

install(TARGETS
  pid_tuner
  DESTINATION lib/${PROJECT_NAME})

install(
  DIRECTORY
    include
    launch
    worlds
    models
  DESTINATION
    share/${PROJECT_NAME}/
)

ament_package()
