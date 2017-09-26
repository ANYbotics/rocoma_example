/*
 * MySharedModule.hpp
 *
 *  Created on: Sep 25, 2017
 *      Author: Gabriel Hottiger
 */

#pragma once

#include "roco/controllers/controllers.hpp"

namespace rocomaex_model {

class MySharedModule : virtual public roco::SharedModule {
 public:
  MySharedModule() = default;
  virtual ~MySharedModule() = default;

  // Initializes the internal state
  virtual bool create(double dt) override {
    internalState_ = 0.0;
    return true;
  }

  // Function increments internal state and returns it to the caller
  bool foo(double& state) {
    internalState_ += 2.34;
    state = internalState_;
    return true;
  }

 protected:
  // Some internal state
  double internalState_;
};

}

