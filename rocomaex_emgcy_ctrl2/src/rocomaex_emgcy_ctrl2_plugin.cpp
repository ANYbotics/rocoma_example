/*!
* @file 	  rocomaex_emgcy_ctrl2_plugin.cpp
* @author   Gabriel Hottiger
* @date		  25/09/2017
* @version 	1.0
* @brief    Plugin export for controller EmergencyController2.
*/

// state and command
#include "rocomaex_model/RocoState.hpp"
#include "rocomaex_model/RocoCommand.hpp"

// rocomaex_emgcy_ctrl2
#include "rocomaex_emgcy_ctrl2/EmergencyController2.hpp"

// rocoma_plugin
#include "rocoma_plugin/rocoma_plugin.hpp"

// export controller plugin
ROCOMA_EXPORT_EMERGENCY_CONTROLLER(
  EmergencyController2,
  rocomaex_model::RocoState,
  rocomaex_model::RocoCommand,
  rocomaex_emgcy_ctrl2::EmergencyController2
);
