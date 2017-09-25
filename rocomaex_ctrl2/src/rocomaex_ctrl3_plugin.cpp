/*!
* @file 	  rocomaex_ctrl3_plugin.cpp
* @author   Gabriel Hottiger
* @date		  25/09/2017
* @version 	1.0
* @brief    Plugin export for controller Controller2.
*/

// state and command
#include "rocomaex_model/RocoState.hpp"
#include "rocomaex_model/RocoCommand.hpp"

// rocomaex_ctrl1
#include "rocomaex_ctrl1/Controller1.hpp"

// rocomaex_ctrl2
#include "rocomaex_ctrl2/Controller2.hpp"

// rocoma_plugin
#include "rocoma_plugin/rocoma_plugin.hpp"

// export controller plugin
ROCOMA_EXPORT_CONTROLLER_TUPLE(
  Controller3,
  rocomaex_model::RocoState,
  rocomaex_model::RocoCommand,
  rocomaex_ctrl1::Controller1,
  rocomaex_ctrl2::Controller2
);
