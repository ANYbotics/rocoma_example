/*!
* @file 	  EmergencyControllerRos1.cpp
* @author   Gabriel Hottiger
* @date		  25/09/2017
* @version 	1.0
* @brief    A controller that ...
*/

// rocomaex_ros_emgcy_ctrl1
#include "rocomaex_ros_emgcy_ctrl1/EmergencyControllerRos1.hpp"

namespace rocomaex_ros_emgcy_ctrl1 {

EmergencyControllerRos1::EmergencyControllerRos1()
    : Base()
{
  setName("EmergencyControllerRos1");
}

EmergencyControllerRos1::~EmergencyControllerRos1() {

}

bool EmergencyControllerRos1::create(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

bool EmergencyControllerRos1::initialize(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");
  return true;
}

bool EmergencyControllerRos1::advance(double dt) {
  MELO_INFO_THROTTLE_STREAM(1.0, "Controller " << this->getName() << " is advanced!");
  return true;
}

bool EmergencyControllerRos1::reset(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is reset!");
  return EmergencyControllerRos1::initialize(dt);
}

bool EmergencyControllerRos1::preStop() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is pre-stopped!");
  return true;
}

bool EmergencyControllerRos1::stop() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is stopped!");
  return true;
}

bool EmergencyControllerRos1::cleanup() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is cleaned up!");
  return true;
}

bool EmergencyControllerRos1::swap(double dt, const roco::ControllerSwapStateInterfacePtr& swapState) {
  // Call current class reset / initialize
  return isInitialized() ? EmergencyControllerRos1::reset(dt) : EmergencyControllerRos1::initialize(dt);
}

bool EmergencyControllerRos1::getSwapState(roco::ControllerSwapStateInterfacePtr& swapState) {
  swapState.reset(nullptr);
  return true;
}

bool EmergencyControllerRos1::addSharedModule(const roco::SharedModulePtr& module) {
  return false;
}

bool EmergencyControllerRos1::initializeFast(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is fast initialized!");
  return true;
}

} /* namespace rocomaex_ros_emgcy_ctrl1 */
