cmake_minimum_required(VERSION 2.8.3)
project(rocoma_example)

find_package(catkin REQUIRED COMPONENTS
  any_node
  rocoma_ros
  roco
  message_logger
  rocomaex_ctrl1
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS any_node rocoma_ros roco message_logger rocomaex_ctrl1
  DEPENDS
)

###########
## Build ##
###########
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/RocomaExample.cpp
)

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

# Declare a C++ executable
add_executable(${PROJECT_NAME}_node src/${PROJECT_NAME}_node.cpp)

add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_node
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)