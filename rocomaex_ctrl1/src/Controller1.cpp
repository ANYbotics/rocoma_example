/**
 * Copyright (c) 2016, Gabriel Hottiger
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Robotics Systems Lab, ETH Zurich nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL  Gabriel Hottiger BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/*!
 * @file    Controller1.cpp
 * @author  Gabriel Hottiger
 * @date    Jul, 2016
 */

// rocomaex ctrl1
#include "rocomaex_ctrl1/Controller1.hpp"

// rocoma plugin
#include "rocoma_plugin/rocoma_plugin.hpp"

// Boost
#include <boost/thread.hpp>

/**
 * Helper macro that wraps pluginlib's PLUGINLIB_EXPORT_CLASS(). Needed because of complicated template syntax.
 * @param Name of the controller plugin, also name of derived class in plugin xml file
 * @param State class the controller is templated on
 * @param Command class the controller is templated on
 * @param Type of the controller the plugin should be registered for (this controller)
 */
ROCOMA_EXPORT_CONTROLLER(Controller1Plugin, rocomaex_model::State, rocomaex_model::Command, rocomaex_ctrl1::Controller1)

namespace rocomaex_ctrl1 {

Controller1::Controller1(): Base(),
    printWorkerHandle_()
{
  //IMPORTANT: initialize name in the constructor.
  this->setName(std::string{"Controller1"});
}

Controller1::~Controller1()
{
}

bool Controller1::printState(const roco::WorkerEvent& event) {
  // Protect the state by the shared mutex
  boost::lock_guard<boost::shared_mutex> guardState(getStateMutex());
  MELO_INFO_STREAM("State: " << getState().getValue());
  return true;
}

bool Controller1::create(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

bool Controller1::initialize(double dt)
{
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

bool Controller1::advance(double dt)
{
  /** You can get access the state and set a command accordingly.
   */

  // Here set the command to twice the state
  getCommand().setValue(2*getState().getValue());
  MELO_INFO_THROTTLE_STREAM(1.0, "Controller " << this->getName() << " is advanced!");
  return true;
}

bool Controller1::reset(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is reset!");
  return true;
}

bool Controller1::cleanup()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is cleaned up!");
  return true;
}

bool Controller1::stop()
{
  sleep(20);
  MELO_INFO_STREAM("Controller " << this->getName() << " is stopped!");
  return true;
}

bool Controller1::preStop()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is pre-stopped!");
  return true;
}

}
