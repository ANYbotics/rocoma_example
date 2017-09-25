/*!
* @file 	  EmergencyControllerRos1.hpp
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

namespace rocomaex_ros_emgcy_ctrl1 {

class EmergencyControllerRos1: virtual public roco_ros::ControllerRos<rocomaex_model::RocoState, rocomaex_model::RocoCommand>, public roco::EmergencyControllerAdapteeInterface {

 public:
  typedef roco_ros::ControllerRos<rocomaex_model::RocoState, rocomaex_model::RocoCommand> Base;

  //! Construct EmergencyControllerRos1.
  EmergencyControllerRos1();

  //! Destruct EmergencyControllerRos1.
  virtual ~EmergencyControllerRos1();

 protected:
  //! Create controller EmergencyControllerRos1.
  virtual bool create(double dt);

  //! Initialize controller EmergencyControllerRos1.
  virtual bool initialize(double dt);

  //! Advance controller EmergencyControllerRos1.
  virtual bool advance(double dt);

  //! Reset controller EmergencyControllerRos1.
  virtual bool reset(double dt);

  //! Pre-stop controller EmergencyControllerRos1.
  virtual bool preStop();

  //! Stop controller EmergencyControllerRos1.
  virtual bool stop();

  //! Cleanup controller EmergencyControllerRos1.
  virtual bool cleanup();

  //! Swap to controller EmergencyControllerRos1 with state 'swap'.
  virtual bool swap(double dt, const roco::ControllerSwapStateInterfacePtr& swapState);

  //! Get swap state 'swapState' of controller EmergencyControllerRos1.
  virtual bool getSwapState(roco::ControllerSwapStateInterfacePtr& swapState);

  //! Add shared module 'module' to controller EmergencyControllerRos1.
  virtual bool addSharedModule(const roco::SharedModulePtr& module);

  /**
   * @brief Initialize controller EmergencyControllerRos1 fast. (computation time << dt)
   * @param dt  Controller time step
   */
  virtual bool initializeFast(double dt);


};

} /* namespace rocomaex_ros_emgcy_ctrl1 */
