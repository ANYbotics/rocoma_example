cmake_minimum_required(VERSION 2.8.3)
project(rocomaex_failproof_ctrl1)

add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  pluginlib
  roco
  message_logger
  rocomaex_model
  rocoma_plugin
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS
    roco
    pluginlib
    message_logger
    rocomaex_model
    rocoma_plugin
  DEPENDS
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/FailproofController1.cpp
)

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)
