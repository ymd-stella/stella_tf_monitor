cmake_minimum_required(VERSION 3.8)
project(stella_tf_monitor)

find_package(ament_cmake REQUIRED)
find_package(class_loader REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(pluginlib REQUIRED)
find_package(diagnostic_updater REQUIRED)
find_package(tf2_ros REQUIRED)

set(dependencies
  class_loader
  rclcpp
  rclcpp_components
  pluginlib
  diagnostic_updater
  tf2_ros
)

add_library(stella_tf_monitor SHARED
  src/stella_tf_monitor.cpp)
target_include_directories(stella_tf_monitor PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_target_dependencies(stella_tf_monitor
  ${dependencies}
)
rclcpp_components_register_node(stella_tf_monitor PLUGIN "stella_tf_monitor::StellaTfMonitor" EXECUTABLE stella_tf_monitor_node)

install(
  DIRECTORY include/
  DESTINATION include
)

install(TARGETS
  stella_tf_monitor
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)

install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME})

ament_package()
