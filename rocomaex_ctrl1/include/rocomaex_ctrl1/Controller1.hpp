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

class Controller1: public roco::Controller<rocomaex_model::State, rocomaex_model::Command>
  {
  public:
    typedef roco::Controller<rocomaex_model::State, rocomaex_model::Command> Base;

  public:

    Controller1();
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
