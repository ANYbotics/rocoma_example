/*!
* @file 	  EmergencyController2.hpp
* @author   Gabriel Hottiger
* @date		  25/09/2017
* @version 	1.0
* @brief    A controller that ...
*/

#pragma once

// roco
#include "roco/controllers/controllers.hpp"

// state and command
#include "rocomaex_model/RocoState.hpp"
#include "rocomaex_model/RocoCommand.hpp"

namespace rocomaex_emgcy_ctrl2 {

class EmergencyController2: virtual public roco::Controller<rocomaex_model::RocoState, rocomaex_model::RocoCommand>, public roco::EmergencyControllerAdapteeInterface {

 public:
  typedef roco::Controller<rocomaex_model::RocoState, rocomaex_model::RocoCommand> Base;

  //! Construct EmergencyController2.
  EmergencyController2();

  //! Destruct EmergencyController2.
  virtual ~EmergencyController2();

 protected:
  //! Create controller EmergencyController2.
  virtual bool create(double dt);

  //! Initialize controller EmergencyController2.
  virtual bool initialize(double dt);

  //! Advance controller EmergencyController2.
  virtual bool advance(double dt);

  //! Reset controller EmergencyController2.
  virtual bool reset(double dt);

  //! Pre-stop controller EmergencyController2.
  virtual bool preStop();

  //! Stop controller EmergencyController2.
  virtual bool stop();

  //! Cleanup controller EmergencyController2.
  virtual bool cleanup();

  //! Swap to controller EmergencyController2 with state 'swap'.
  virtual bool swap(double dt, const roco::ControllerSwapStateInterfacePtr& swapState);

  //! Get swap state 'swapState' of controller EmergencyController2.
  virtual bool getSwapState(roco::ControllerSwapStateInterfacePtr& swapState);

  //! Add shared module 'module' to controller EmergencyController2.
  virtual bool addSharedModule(const roco::SharedModulePtr& module);

  /**
   * @brief Initialize controller EmergencyController2 fast. (computation time << dt)
   * @param dt  Controller time step
   */
  virtual bool initializeFast(double dt);


};

} /* namespace rocomaex_emgcy_ctrl2 */
