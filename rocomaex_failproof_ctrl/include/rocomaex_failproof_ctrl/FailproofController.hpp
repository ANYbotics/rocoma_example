/*
 * FailproofController.hpp
 *
 *  Created on: Jul 27, 2016
 *      Author: Gabriel Hottiger
 */

#pragma once

#include "roco/controllers/FailproofController.hpp"

#include "rocomaex_model/State.hpp"
#include "rocomaex_model/Command.hpp"

namespace rocoma_example {

class FailproofController:public roco::FailproofController<rocoma_example::State, rocoma_example::Command> {
 public:
  using Base = roco::FailproofController<rocoma_example::State, rocoma_example::Command>;
 public:

  //! Contstructor
  FailproofController();

  //! Destructor
  virtual ~FailproofController();

  virtual bool create(double dt);

  virtual void advance(double dt);

  virtual bool cleanup();

};

} /* namespace rocoma_example */
