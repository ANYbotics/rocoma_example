/*!
* @file 	  Controller2.hpp
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

namespace rocomaex_ctrl2 {

class Controller2: virtual public roco::Controller<rocomaex_model::RocoState, rocomaex_model::RocoCommand> {

 public:
  typedef roco::Controller<rocomaex_model::RocoState, rocomaex_model::RocoCommand> Base;

  //! Construct Controller2.
  Controller2();

  //! Destruct Controller2.
  virtual ~Controller2();

 protected:
  //! Create controller Controller2.
  virtual bool create(double dt);

  //! Initialize controller Controller2.
  virtual bool initialize(double dt);

  //! Advance controller Controller2.
  virtual bool advance(double dt);

  //! Reset controller Controller2.
  virtual bool reset(double dt);

  //! Pre-stop controller Controller2.
  virtual bool preStop();

  //! Stop controller Controller2.
  virtual bool stop();

  //! Cleanup controller Controller2.
  virtual bool cleanup();

  //! Swap to controller Controller2 with state 'swap'.
  virtual bool swap(double dt, const roco::ControllerSwapStateInterfacePtr& swapState);

  //! Get swap state 'swapState' of controller Controller2.
  virtual bool getSwapState(roco::ControllerSwapStateInterfacePtr& swapState);

  //! Add shared module 'module' to controller Controller2.
  virtual bool addSharedModule(const roco::SharedModulePtr& module);

 private:
  std::shared_ptr<rocomaex_model::MySharedModule> sm_;


};

} /* namespace rocomaex_ctrl2 */
