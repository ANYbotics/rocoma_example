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
 * @file    EmergencyController2.cpp
 * @author  Gabriel Hottiger
 * @date    Jul, 2016
 */

// rocomaex ctrl2
#include "rocomaex_emgcy_ctrl2/EmergencyController2.hpp"

// pluginlib
#include <pluginlib/class_list_macros.h>

// rocoma plugin
#include "rocoma_plugin/plugins/EmergencyControllerPlugin.hpp"
#include "rocoma_plugin/plugins/ControllerPlugin.hpp"

/**
 * Helper macro that wraps pluginlib's PLUGINLIB_EXPORT_CLASS(). Needed because of complicated template syntax.
 * @param Name of the controller plugin, also name of derived class in plugin xml file
 * @param State class the controller is templated on
 * @param Command class the controller is templated on
 * @param Type of the controller the plugin should be registered for (this controller)
 */
ROCOMA_EXPORT_EMERGENCY_CONTROLLER(EmergencyController2Plugin, rocomaex_model::State, rocomaex_model::Command, rocomaex_emgcy_ctrl2::EmergencyController2)
ROCOMA_EXPORT_CONTROLLER(EmergencyController2Plugin, rocomaex_model::State, rocomaex_model::Command, rocomaex_emgcy_ctrl2::EmergencyController2)

namespace rocomaex_emgcy_ctrl2 {

EmergencyController2::EmergencyController2(): Base()
{
  //IMPORTANT: initialize name in the constructor.
  this->name_ = "EmergencyController2";
}

EmergencyController2::~EmergencyController2()
{
}

bool EmergencyController2::create(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

bool EmergencyController2::initialize(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");
  return true;
}

bool EmergencyController2::advance(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is advanced!");
  return true;
}

bool EmergencyController2::reset(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is reset!");
  return true;
}

bool EmergencyController2::cleanup()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is cleaned up!");
  return true;
}

bool EmergencyController2::stop()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is stopped!");
  return true;
}

bool EmergencyController2::preStop()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is pre-stopped!");
  return true;
}

bool EmergencyController2::initializeFast(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is fast initialized!");
  return true;
}

}
