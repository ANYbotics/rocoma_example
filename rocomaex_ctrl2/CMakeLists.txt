cmake_minimum_required(VERSION 2.8.3)

project(rocomaex_ctrl2)
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
  src/Controller2.cpp
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_dependencies(${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
)

add_library(${PROJECT_NAME}_plugin
  src/rocomaex_ctrl2_plugin.cpp
)

target_link_libraries(${PROJECT_NAME}_plugin
  ${catkin_LIBRARIES}
  ${PROJECT_NAME}
)

find_package(rocomaex_ctrl1)

include_directories(${rocomaex_ctrl1_INCLUDE_DIRS})

add_library(rocomaex_ctrl3_plugin
  src/rocomaex_ctrl3_plugin.cpp
)

target_link_libraries(rocomaex_ctrl3_plugin
  ${catkin_LIBRARIES}
  ${PROJECT_NAME}
  ${rocomaex_ctrl1_LIBRARIES}
)

find_package(rocomaex_emgcy_ctrl1)

include_directories(${rocomaex_emgcy_ctrl1_INCLUDE_DIRS})

add_library(rocomaex_ctrl4_plugin
  src/rocomaex_ctrl4_plugin.cpp
)

target_link_libraries(rocomaex_ctrl4_plugin
  ${catkin_LIBRARIES}
  ${PROJECT_NAME}
  ${rocomaex_emgcy_ctrl1_LIBRARIES}
)

install(FILES rocoma_plugin.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_plugin rocomaex_ctrl3_plugin rocomaex_ctrl4_plugin
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
