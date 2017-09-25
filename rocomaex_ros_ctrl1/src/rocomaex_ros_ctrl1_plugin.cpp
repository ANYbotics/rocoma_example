/*!
* @file 	  rocomaex_ros_ctrl1_plugin.cpp
* @author   Gabriel Hottiger
* @date		  25/09/2017
* @version 	1.0
* @brief    Plugin export for controller ControllerRos1.
*/

// state and command
#include "rocomaex_model/RocoState.hpp"
#include "rocomaex_model/RocoCommand.hpp"

// rocomaex_ros_ctrl1
#include "rocomaex_ros_ctrl1/ControllerRos1.hpp"

// rocoma_plugin
#include "rocoma_plugin/rocoma_plugin.hpp"

// export controller plugin
ROCOMA_EXPORT_CONTROLLER_ROS(
  ControllerRos1,
  rocomaex_model::RocoState,
  rocomaex_model::RocoCommand,
  rocomaex_ros_ctrl1::ControllerRos1
);
