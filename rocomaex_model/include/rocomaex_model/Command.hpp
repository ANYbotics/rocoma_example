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

// Stl
#include <algorithm>

namespace rocomaex_model {

class Command: public roco::CommandInterface {

 public:

  Command(): roco::CommandInterface(),
             value_()
  {

  }

  ~Command()
  {

  }

  bool limitCommand() {
    // Limit the command to a maximum of 5.0
    value_ = std::min(5.0, value_);
    MELO_INFO_THROTTLE_STREAM(1.0, "[rocoma_example::Command]: Limiting Command");
    return true;
  }

  void setValue(const double value) {
    value_ = value;
  }

  double getValue() const{
    return value_;
  }

 private:
  double value_;

};

}
