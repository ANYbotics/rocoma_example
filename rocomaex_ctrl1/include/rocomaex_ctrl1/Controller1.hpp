/*!
* @file 	  Controller1.hpp
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
#include "rocomaex_model/MySharedModule.hpp"

namespace rocomaex_ctrl1 {

class Controller1: virtual public roco::Controller<rocomaex_model::RocoState, rocomaex_model::RocoCommand> {

 public:
  typedef roco::Controller<rocomaex_model::RocoState, rocomaex_model::RocoCommand> Base;

  //! Construct Controller1.
  Controller1();

  //! Destruct Controller1.
  virtual ~Controller1();

 protected:
  //! Print rocoma example state
  bool printState(const roco::WorkerEvent& event);

  //! Create controller Controller1.
  virtual bool create(double dt);

  //! Initialize controller Controller1.
  virtual bool initialize(double dt);

  //! Advance controller Controller1.
  virtual bool advance(double dt);

  //! Reset controller Controller1.
  virtual bool reset(double dt);

  //! Pre-stop controller Controller1.
  virtual bool preStop();

  //! Stop controller Controller1.
  virtual bool stop();

  //! Cleanup controller Controller1.
  virtual bool cleanup();

  //! Swap to controller Controller1 with state 'swap'.
  virtual bool swap(double dt, const roco::ControllerSwapStateInterfacePtr& swapState);

  //! Get swap state 'swapState' of controller Controller1.
  virtual bool getSwapState(roco::ControllerSwapStateInterfacePtr& swapState);

  //! Add shared module 'module' to controller Controller1.
  virtual bool addSharedModule(const roco::SharedModulePtr& module);

private:
  roco::WorkerHandle printWorkerHandle_;
  std::shared_ptr<rocomaex_model::MySharedModule> sm_;

};

} /* namespace rocomaex_ctrl1 */
