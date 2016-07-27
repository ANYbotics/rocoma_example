/*
 * Command.hpp
 *
 *  Created on: Jul 27, 2016
 *      Author: Gabriel Hottiger
 */

#pragma once

#include "roco/model/CommandInterface.hpp"

#include "message_logger/message_logger.hpp"

namespace rocoma_example {

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
