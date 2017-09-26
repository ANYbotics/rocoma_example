/*!
* @file 	  Controller2.cpp
* @author   Gabriel Hottiger
* @date		  25/09/2017
* @version 	1.0
* @brief    A controller that ...
*/

// rocomaex_ctrl2
#include "rocomaex_ctrl2/Controller2.hpp"
#include "rocomaex_model/MySwapState.hpp"

namespace rocomaex_ctrl2 {

Controller2::Controller2()
    : Base()
{
  setName("Controller2");
}

Controller2::~Controller2() {

}

bool Controller2::create(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

bool Controller2::initialize(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");
  return true;
}

bool Controller2::advance(double dt) {
  MELO_INFO_THROTTLE_STREAM(1.0, "Controller " << this->getName() << " is advanced!");
  if(sm_ != nullptr) {
    double sharedModuleState;
    if(sm_->foo(sharedModuleState)){
      MELO_INFO_THROTTLE_STREAM(1.0, "Controller " << this->getName() << " shared module state is " << sharedModuleState << ".");
    }
  }
  return true;
}

bool Controller2::reset(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is reset!");
  return Controller2::initialize(dt);
}

bool Controller2::preStop() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is pre-stopped!");
  return true;
}

bool Controller2::stop() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is stopped!");
  return true;
}

bool Controller2::cleanup() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is cleaned up!");
  return true;
}

bool Controller2::swap(double dt, const roco::ControllerSwapStateInterfacePtr& swapState) {
  if(Controller2::initialize(dt)) {
    // Build up vector of pointers
    std::vector<roco::ControllerSwapStateInterface *> states;

    // First check if tuple state
    roco::ControllerTupleSwapState * tupleState = dynamic_cast<roco::ControllerTupleSwapState *>(swapState.get());
    if(tupleState != nullptr) {
      for(auto& s : tupleState->getSwapStates() ) { states.push_back(s.get()); }
    } else {
      states.push_back(swapState.get());
    }
    for(auto& state : states) {
      rocomaex_model::MySwapState * myState = dynamic_cast<rocomaex_model::MySwapState * >(state);
      if(myState != nullptr) {
        MELO_INFO_STREAM("Controller " << this->getName() << " got state with value " << myState->getState() << " during swap!");
      }
    }
    return true;
  }
  return false;
}

bool Controller2::getSwapState(roco::ControllerSwapStateInterfacePtr& swapState) {
  swapState.reset(nullptr);
  return true;
}

bool Controller2::addSharedModule(const roco::SharedModulePtr& module) {
  auto sm = std::dynamic_pointer_cast<rocomaex_model::MySharedModule>(module);
  if( sm != nullptr ) { sm_ = sm; }
  return sm != nullptr;
}

} /* namespace rocomaex_ctrl2 */
