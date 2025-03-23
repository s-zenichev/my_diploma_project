cmake_minimum_required(VERSION 3.8)
project(puma560_description)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(puma560_gazebo REQUIRED)
find_package(urdf REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(ament_index_cpp REQUIRED)

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

set (SOURCES
    src/control_system.cpp
    src/pid.cpp)

set (HEADERS
    include/pid.h)
add_executable(control_system ${HEADERS} ${SOURCES})
target_include_directories(control_system PRIVATE include)
target_link_libraries(control_system yaml-cpp)
ament_target_dependencies(control_system rclcpp std_msgs sensor_msgs)

install(TARGETS
  control_system
  DESTINATION lib/${PROJECT_NAME})

install(
  DIRECTORY
    config
    launch
    urdf
    meshes
    rviz
  DESTINATION
    share/${PROJECT_NAME}/
)

ament_package()
