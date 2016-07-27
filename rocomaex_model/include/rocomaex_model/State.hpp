/*
 * State.hpp
 *
 *  Created on: Jul 27, 2016
 *      Author: Gabriel Hottiger
 */

#pragma once

#include "roco/model/StateInterface.hpp"

#include "message_logger/message_logger.hpp"

namespace rocoma_example {

class State: public roco::StateInterface {

  State(): roco::StateInterface()
  {

  }

  ~State()
  {

  }

  bool checkState() {
    MELO_INFO("[rocoma_example::State]: Checking State");
    return true;
  }

};

}
