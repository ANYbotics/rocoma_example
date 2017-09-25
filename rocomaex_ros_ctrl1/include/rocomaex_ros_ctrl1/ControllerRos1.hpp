/*!
* @file 	  ControllerRos1.hpp
* @author   Gabriel Hottiger
* @date		  25/09/2017
* @version 	1.0
* @brief    A controller that ...
*/

#pragma once

// roco_ros
#include "roco_ros/controllers/controllers.hpp"

// state and command
#include "rocomaex_model/RocoState.hpp"
#include "rocomaex_model/RocoCommand.hpp"

namespace rocomaex_ros_ctrl1 {

class ControllerRos1: virtual public roco_ros::ControllerRos<rocomaex_model::RocoState, rocomaex_model::RocoCommand> {

 public:
  typedef roco_ros::ControllerRos<rocomaex_model::RocoState, rocomaex_model::RocoCommand> Base;

  //! Construct ControllerRos1.
  ControllerRos1();

  //! Destruct ControllerRos1.
  virtual ~ControllerRos1();

 protected:
  //! Create controller ControllerRos1.
  virtual bool create(double dt);

  //! Initialize controller ControllerRos1.
  virtual bool initialize(double dt);

  //! Advance controller ControllerRos1.
  virtual bool advance(double dt);

  //! Reset controller ControllerRos1.
  virtual bool reset(double dt);

  //! Pre-stop controller ControllerRos1.
  virtual bool preStop();

  //! Stop controller ControllerRos1.
  virtual bool stop();

  //! Cleanup controller ControllerRos1.
  virtual bool cleanup();

  //! Swap to controller ControllerRos1 with state 'swap'.
  virtual bool swap(double dt, const roco::ControllerSwapStateInterfacePtr& swapState);

  //! Get swap state 'swapState' of controller ControllerRos1.
  virtual bool getSwapState(roco::ControllerSwapStateInterfacePtr& swapState);

  //! Add shared module 'module' to controller ControllerRos1.
  virtual bool addSharedModule(const roco::SharedModulePtr& module);


};

} /* namespace rocomaex_ros_ctrl1 */
