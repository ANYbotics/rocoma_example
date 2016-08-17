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
#include "rocomaex_ros_ctrl1/ControllerRos1.hpp"

// pluginlib
#include <pluginlib/class_list_macros.h>

// rocoma plugin
#include "rocoma_plugin/interfaces/ControllerRosPluginInterface.hpp"
#include "rocoma_plugin/plugins/ControllerRosPlugin.hpp"

/**
 * Helper macro that wraps pluginlib's PLUGINLIB_EXPORT_CLASS(). Needed because of complicated template syntax.
 * @param Name of the controller plugin, also name of derived class in plugin xml file
 * @param State class the controller is templated on
 * @param Command class the controller is templated on
 * @param Type of the controller the plugin should be registered for (this controller)
 */
ROCOMA_EXPORT_CONTROLLER_ROS(ControllerRos1Plugin, rocomaex_model::State, rocomaex_model::Command, rocomaex_ros_ctrl1::ControllerRos1)

namespace rocomaex_ros_ctrl1 {

ControllerRos1::ControllerRos1(): Base()
{
  //IMPORTANT: initialize name in the constructor.
  this->name_ = "ControllerRos1";
}

ControllerRos1::~ControllerRos1()
{
}

bool ControllerRos1::create(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

bool ControllerRos1::initialize(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");
  return true;
}

bool ControllerRos1::advance(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is advanced!");
  return true;
}

bool ControllerRos1::reset(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is reset!");
  return true;
}

bool ControllerRos1::cleanup()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is cleaned up!");
  return true;
}

bool ControllerRos1::stop()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is stopped!");
  return true;
}

bool ControllerRos1::preStop()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is pre-stopped!");
  return true;
}

}
