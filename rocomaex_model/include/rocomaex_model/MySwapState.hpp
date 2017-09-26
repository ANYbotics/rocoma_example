/*
 * MySharedModule.hpp
 *
 *  Created on: Sep 25, 2017
 *      Author: Gabriel Hottiger
 */

#pragma once

#include "roco/controllers/controllers.hpp"

namespace rocomaex_model {

class MySwapState : public roco::ControllerSwapStateInterface {
 public:
  MySwapState(const double state): state_(state) { }
  ~MySwapState() = default;

  virtual bool operator== ( const ControllerSwapStateInterface& state ) const {
    try {
      const MySwapState& item = dynamic_cast<const MySwapState&>(state);
      return ( (state_ == item.getState()));
    } catch(const std::bad_cast& e) {
      return false;
    }
  }
  double getState() const { return state_; }

 private:
  double state_;
};

}

