/*
 * Crawling_Task.hpp
 *
 *  Created on: Aug 20, 2014
 *      Author: C. Dario Bellicoso
 */

#pragma once

#include "rocomaex_model/State.hpp"
#include "rocomaex_model/Command.hpp"

#include "roco/controllers/Controller.hpp"

namespace rocomaex_ctrl1 {

class Controller1: public roco::Controller<rocoma_example::State, rocoma_example::Command>
  {
  public:
    typedef roco::Controller<rocoma_example::State, rocoma_example::Command> Base;

  public:

    Controller1();
    explicit Controller1(const std::string& controllerName);
    virtual ~Controller1();

    virtual bool create(double dt);
    virtual bool initialize(double dt);
    virtual bool advance(double dt);
    virtual bool reset(double dt);
    virtual bool cleanup();
    virtual bool stop();
    virtual bool preStop();

};

} // namespace rocomaex_ctrl1
