cmake_minimum_required(VERSION 3.5.1)

project(rocomaex_emgcy_ctrl2)
# Load catkin and all dependencies required for this package
find_package(catkin REQUIRED COMPONENTS
  roco
  rocomaex_model
  message_logger
  rocoma_plugin
)

# Flags
add_definitions(-std=c++11)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS
    roco
    rocomaex_model
    message_logger
    rocoma_plugin
)

include_directories(include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/EmergencyController2.cpp
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_dependencies(${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
)

add_library(${PROJECT_NAME}_plugin
  src/${PROJECT_NAME}_plugin.cpp
)

target_link_libraries(${PROJECT_NAME}_plugin
  ${catkin_LIBRARIES}
  ${PROJECT_NAME}
)

add_library(rocomaex_ctrl5_plugin
  src/rocomaex_ctrl5_plugin.cpp
)

target_link_libraries(rocomaex_ctrl5_plugin
  ${catkin_LIBRARIES}
  ${PROJECT_NAME}
)

install(FILES rocoma_plugin.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_plugin
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
