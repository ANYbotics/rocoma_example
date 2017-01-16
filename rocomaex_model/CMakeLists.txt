cmake_minimum_required(VERSION 2.8.3)
project(rocomaex_model)

add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roco
  message_logger
  )

catkin_package(
  INCLUDE_DIRS include
  #LIBRARIES
  CATKIN_DEPENDS roco message_logger
  #DEPENDS
)
