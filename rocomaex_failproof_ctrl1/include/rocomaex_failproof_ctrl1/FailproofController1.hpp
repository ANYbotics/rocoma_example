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
 * @file    FailproofController1.hpp
 * @author  Gabriel Hottiger
 * @date    Jul, 2016
 */

#pragma once

// roco
#include "roco/controllers/FailproofController.hpp"

// rocomaex model
#include "rocomaex_model/RocoState.hpp"
#include "rocomaex_model/RocoCommand.hpp"

namespace rocomaex_failproof_ctrl1 {

//! Example class for a robot controller implementing the roco::FailproofControllerAdapteeInterface
/**
 * IMPORTANT: Make sure to use virtual inheritance, prevents issues due to multiple inheritance
 */
class FailproofController1: virtual public roco::FailproofController<rocomaex_model::RocoState, rocomaex_model::RocoCommand>
{

 public:
  //! Convenience typedef for Base class
  typedef roco::FailproofController<rocomaex_model::RocoState, rocomaex_model::RocoCommand> Base;

 public:
  /** Default Constructor
      NOTE: Other constructors can't be invoked when using the plugin mechanism
   */
  FailproofController1();
  //! Destructor
  virtual ~FailproofController1();

  /** Adaptee Implementation
        NOTE: Adaptee functionality is hidden from the client
   */
 protected:
  virtual bool create(double dt);
  virtual void advance(double dt);
  virtual bool cleanup();

};

} // namespace rocomaex_failproof_ctrl1
