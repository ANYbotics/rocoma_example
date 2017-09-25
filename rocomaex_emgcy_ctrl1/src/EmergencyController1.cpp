/*!
* @file 	  EmergencyController1.cpp
* @author   Gabriel Hottiger
* @date		  25/09/2017
* @version 	1.0
* @brief    A controller that ...
*/

// rocomaex_emgcy_ctrl1
#include "rocomaex_emgcy_ctrl1/EmergencyController1.hpp"

namespace rocomaex_emgcy_ctrl1 {

EmergencyController1::EmergencyController1()
    : Base()
{
  setName("EmergencyController1");
}

EmergencyController1::~EmergencyController1() {

}

bool EmergencyController1::create(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

bool EmergencyController1::initialize(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");
  return true;
}

bool EmergencyController1::advance(double dt) {
  MELO_INFO_THROTTLE_STREAM(1.0, "Controller " << this->getName() << " is advanced!");
  return true;
}

bool EmergencyController1::reset(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is reset!");
  return EmergencyController1::initialize(dt);
}

bool EmergencyController1::preStop() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is pre-stopped!");
  return true;
}

bool EmergencyController1::stop() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is stopped!");
  return true;
}

bool EmergencyController1::cleanup() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is cleaned up!");
  return true;
}

bool EmergencyController1::swap(double dt, const roco::ControllerSwapStateInterfacePtr& swapState) {
  // Call current class reset / initialize
  return isInitialized() ? EmergencyController1::reset(dt) : EmergencyController1::initialize(dt);
}

bool EmergencyController1::getSwapState(roco::ControllerSwapStateInterfacePtr& swapState) {
  swapState.reset(nullptr);
  return true;
}

bool EmergencyController1::addSharedModule(const roco::SharedModulePtr& module) {
  return false;
}

bool EmergencyController1::initializeFast(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is fast initialized!");
  return true;
}

} /* namespace rocomaex_emgcy_ctrl1 */
