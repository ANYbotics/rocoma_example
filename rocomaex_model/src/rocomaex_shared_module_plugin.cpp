/*!
* @file 	  rocomaex_shared_module_plugin.cpp
* @author   Gabriel Hottiger
* @date		  25/09/2017
* @version 	1.0
* @brief    Plugin export for controller Controller1.
*/

// rocomaex_model
#include "rocomaex_model/MySharedModule.hpp"

// rocoma_plugin
#include "rocoma_plugin/rocoma_plugin.hpp"

// export shared module plugin
ROCOMA_EXPORT_SHARED_MODULE(
  MySharedModule,
  rocomaex_model::MySharedModule
);
