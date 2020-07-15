cmake_minimum_required(VERSION 3.5.1)
project(rocoma_example)

find_package(Boost REQUIRED)

## Find catkin
find_package(catkin REQUIRED COMPONENTS
  message_logger
  roco
  rocoma
  rocomaex_model
  rocomaex_ctrl1
  rocomaex_ctrl2
  rocomaex_emgcy_ctrl1
  rocomaex_emgcy_ctrl2
  rocomaex_failproof_ctrl1
)

## Catkin package configuration

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS
    message_logger
    roco
    rocoma
    rocomaex_model
    rocomaex_ctrl1
    rocomaex_ctrl2
    rocomaex_emgcy_ctrl1
    rocomaex_emgcy_ctrl2
    rocomaex_failproof_ctrl1
  DEPENDS Boost
)

## Build

add_definitions(-std=c++11)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

# Library
add_library(${PROJECT_NAME}
  src/RocomaExample.cpp
)

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

# Executable
add_executable(${PROJECT_NAME}_exec src/${PROJECT_NAME}.cpp)

add_dependencies(${PROJECT_NAME}_exec ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(${PROJECT_NAME}_exec
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

#############
## Install ##
#############
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  PATTERN ".svn" EXCLUDE
)
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
