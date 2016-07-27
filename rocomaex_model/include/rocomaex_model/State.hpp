/*
 * State.hpp
 *
 *  Created on: Jul 27, 2016
 *      Author: Gabriel Hottiger
 */

#pragma once

// roco
#include "roco/model/StateInterface.hpp"

// message logger
#include "message_logger/message_logger.hpp"

namespace rocomaex_model {

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
