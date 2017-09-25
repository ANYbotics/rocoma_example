/*!
* @file 	  Controller1.cpp
* @author   Gabriel Hottiger
* @date		  25/09/2017
* @version 	1.0
* @brief    A controller that ...
*/

// rocomaex_ctrl1
#include "rocomaex_ctrl1/Controller1.hpp"

// boost
#include <boost/thread/shared_mutex.hpp>
#include <boost/bind.hpp>

namespace rocomaex_ctrl1 {

Controller1::Controller1()
    : Base()
{
  setName("Controller1");
}

Controller1::~Controller1() {

}

bool Controller1::printState(const roco::WorkerEvent& event) {
  // Protect the state by the shared mutex
  boost::lock_guard<boost::shared_mutex> guardState(getStateMutex());
  MELO_INFO_STREAM("State: " << getState().getValue());
  return true;
}

bool Controller1::create(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

bool Controller1::initialize(double dt) {
  // You can acces the parameter path by getParameterPath()
  MELO_INFO_STREAM("The parameter path of " << this->getName() << " is " << this->getParameterPath());
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");

  /*** Roco/ Rocoma also features multithreading capabilities.
   *   This worker displays the state.
   */
  roco::WorkerOptions publishWorkerOptions;
  publishWorkerOptions.autostart_ = false;            // do not auto start
  publishWorkerOptions.frequency_ = 10.0;             // publish with 10 Hz
  publishWorkerOptions.name_ = "print_state_command"; // thread name
  publishWorkerOptions.priority_ = 0;                 // priority
  publishWorkerOptions.synchronous_ = false;
  publishWorkerOptions.callback_ = boost::bind(&Controller1::printState, this, _1);
  printWorkerHandle_ = addWorker(publishWorkerOptions);
  startWorker(printWorkerHandle_);
  //---

  return true;
}

bool Controller1::advance(double dt) {
  // Set the command to twice the state
  getCommand().setValue(2*getState().getValue());
  MELO_INFO_THROTTLE_STREAM(1.0, "Controller " << this->getName() << " is advanced!");
  return true;
}

bool Controller1::reset(double dt) {
  MELO_INFO_STREAM("Controller " << this->getName() << " is reset!");
  return Controller1::initialize(dt);
}

bool Controller1::preStop() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is pre-stopped!");
  cancelWorker(printWorkerHandle_);
  return true;
}

bool Controller1::stop() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is stopped!");
  return true;
}

bool Controller1::cleanup() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is cleaned up!");
  return true;
}

bool Controller1::swap(double dt, const roco::ControllerSwapStateInterfacePtr& swapState) {
  // Call current class reset / initialize
  return isInitialized() ? Controller1::reset(dt) : Controller1::initialize(dt);
}

bool Controller1::getSwapState(roco::ControllerSwapStateInterfacePtr& swapState) {
  swapState.reset(nullptr);
  return true;
}

bool Controller1::addSharedModule(const roco::SharedModulePtr& module) {
  return false;
}



} /* namespace rocomaex_ctrl1 */
