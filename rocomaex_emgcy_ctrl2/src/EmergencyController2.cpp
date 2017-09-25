/*!
* @file 	  EmergencyController2.cpp
* @author   Gabriel Hottiger
* @date		  25/09/2017
* @version 	1.0
* @brief    A controller that ...
*/

// rocomaex_emgcy_ctrl2
#include "rocomaex_emgcy_ctrl2/EmergencyController2.hpp"

namespace rocomaex_emgcy_ctrl2 {

EmergencyController2::EmergencyController2()
    : Base()
{
  setName("EmergencyController2");
}

EmergencyController2::~EmergencyController2() {

}

bool EmergencyController2::create(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

bool EmergencyController2::initialize(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");
  return true;
}

bool EmergencyController2::advance(double dt) {
  MELO_INFO_THROTTLE_STREAM(1.0, "Controller " << this->getName() << " is advanced!");
  return true;
}

bool EmergencyController2::reset(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is reset!");
  return EmergencyController2::initialize(dt);
}

bool EmergencyController2::preStop() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is pre-stopped!");
  return true;
}

bool EmergencyController2::stop() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is stopped!");
  return true;
}

bool EmergencyController2::cleanup() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is cleaned up!");
  return true;
}

bool EmergencyController2::swap(double dt, const roco::ControllerSwapStateInterfacePtr& swapState) {
  // Call current class reset / initialize
  return isInitialized() ? EmergencyController2::reset(dt) : EmergencyController2::initialize(dt);
}

bool EmergencyController2::getSwapState(roco::ControllerSwapStateInterfacePtr& swapState) {
  swapState.reset(nullptr);
  return true;
}

bool EmergencyController2::addSharedModule(const roco::SharedModulePtr& module) {
  return false;
}

bool EmergencyController2::initializeFast(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is fast initialized!");
  return true;
}

} /* namespace rocomaex_emgcy_ctrl2 */
