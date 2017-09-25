/*!
* @file 	  ControllerRos1.cpp
* @author   Gabriel Hottiger
* @date		  25/09/2017
* @version 	1.0
* @brief    A controller that ...
*/

// rocomaex_ros_ctrl1
#include "rocomaex_ros_ctrl1/ControllerRos1.hpp"

namespace rocomaex_ros_ctrl1 {

ControllerRos1::ControllerRos1()
    : Base()
{
  setName("ControllerRos1");
}

ControllerRos1::~ControllerRos1() {

}

bool ControllerRos1::create(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

bool ControllerRos1::initialize(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");
  return true;
}

bool ControllerRos1::advance(double dt) {
  MELO_INFO_THROTTLE_STREAM(1.0, "Controller " << this->getName() << " is advanced!");
  return true;
}

bool ControllerRos1::reset(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is reset!");
  return ControllerRos1::initialize(dt);
}

bool ControllerRos1::preStop() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is pre-stopped!");
  return true;
}

bool ControllerRos1::stop() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is stopped!");
  return true;
}

bool ControllerRos1::cleanup() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is cleaned up!");
  return true;
}

bool ControllerRos1::swap(double dt, const roco::ControllerSwapStateInterfacePtr& swapState) {
  // Call current class reset / initialize
  return isInitialized() ? ControllerRos1::reset(dt) : ControllerRos1::initialize(dt);
}

bool ControllerRos1::getSwapState(roco::ControllerSwapStateInterfacePtr& swapState) {
  swapState.reset(nullptr);
  return true;
}

bool ControllerRos1::addSharedModule(const roco::SharedModulePtr& module) {
  return false;
}



} /* namespace rocomaex_ros_ctrl1 */
