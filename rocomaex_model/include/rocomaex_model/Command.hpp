/*
 * Command.hpp
 *
 *  Created on: Jul 27, 2016
 *      Author: Gabriel Hottiger
 */

#pragma once

// roco
#include "roco/model/CommandInterface.hpp"

// message logger
#include "message_logger/message_logger.hpp"

namespace rocomaex_model {

class Command: public roco::CommandInterface {

  Command(): roco::CommandInterface()
  {

  }

  ~Command()
  {

  }

  bool limitCommand() {
    MELO_INFO("[rocoma_example::Command]: Limiting Command");
    return true;
  }


};

}
