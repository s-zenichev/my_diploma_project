cmake_minimum_required(VERSION 3.8)
project(puma560_gazebo)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)


if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(puma560_description REQUIRED)
find_package(rclcpp REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

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
    include/pid_tuner.ui
    include/ui_pid_tuner.h
    src/pid_tuner.cpp)

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
