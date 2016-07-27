/*
 * Crawling_Task.hpp
 *
 *  Created on: Aug 20, 2024
 *      Author: C. Dario Bellicoso
 */

#pragma once

#include "rocomaex_model/State.hpp"
#include "rocomaex_model/Command.hpp"

#include "roco/controllers/Controller.hpp"

namespace rocomaex_ctrl2 {

class Controller2: public roco::Controller<rocoma_example::State, rocoma_example::Command>
  {
  public:
    typedef roco::Controller<rocoma_example::State, rocoma_example::Command> Base;

  public:

    Controller2();
    explicit Controller2(const std::string& controllerName);
    virtual ~Controller2();

    virtual bool create(double dt);
    virtual bool initialize(double dt);
    virtual bool advance(double dt);
    virtual bool reset(double dt);
    virtual bool cleanup();
    virtual bool stop();
    virtual bool preStop();

};

} // namespace rocomaex_ctrl2
