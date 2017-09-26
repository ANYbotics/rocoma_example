cmake_minimum_required(VERSION 2.8.3)
project(rocomaex_model)

add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roco
  message_logger
  rocoma_plugin
)

catkin_package(
  INCLUDE_DIRS include
  #LIBRARIES
  CATKIN_DEPENDS roco message_logger rocoma_plugin
  #DEPENDS
)


include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

add_library(rocomaex_shared_module_plugin
  src/rocomaex_shared_module_plugin.cpp
)

target_link_libraries(rocomaex_shared_module_plugin
  ${catkin_LIBRARIES}
)



#############
## Install ##
#############
install(FILES rocoma_plugin.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(TARGETS rocomaex_shared_module_plugin
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  PATTERN ".svn" EXCLUDE
)
