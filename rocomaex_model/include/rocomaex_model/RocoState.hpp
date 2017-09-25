/*
 * RocoState.hpp
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

class RocoState: public roco::StateInterface {

 public:

  RocoState(): roco::StateInterface(),
    value_()
  {

  }

  ~RocoState()
  {

  }

  bool checkState() const{
    MELO_INFO_THROTTLE_STREAM(1.0, "[rocoma_example::RocoState]: Checking State");
    return true;
  }

  double getValue() const {
    return value_;
  }

 private:
  double value_;

};

}
