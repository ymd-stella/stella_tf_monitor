cmake_minimum_required(VERSION 3.0.2)
project(stella_tf_monitor)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  nodelet
  pluginlib
  diagnostic_updater
  tf2_ros
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

catkin_package()

add_library(StellaTfMonitorNodelet src/stella_tf_monitor_nodelet.cpp)

target_link_libraries(StellaTfMonitorNodelet
  ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_node
  src/${PROJECT_NAME}_node.cpp)

target_link_libraries(${PROJECT_NAME}_node
  StellaTfMonitorNodelet)

install(TARGETS ${PROJECT_NAME}_node StellaTfMonitorNodelet
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(FILES nodelet_plugins.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
