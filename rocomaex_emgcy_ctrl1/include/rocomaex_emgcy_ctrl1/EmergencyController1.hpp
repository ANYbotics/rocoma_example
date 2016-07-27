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
#include "roco/controllers/adaptees/EmergencyControllerAdapteeInterface.hpp"

namespace rocoma_example {

class EmergencyController1: public roco::Controller<rocoma_example::State, rocoma_example::Command>, public roco::EmergencyControllerAdapteeInterface
  {
  public:
    typedef roco::Controller<rocoma_example::State, rocoma_example::Command> Base;

  public:

    EmergencyController1();
    explicit EmergencyController1(const std::string& controllerName);
    virtual ~EmergencyController1();

    virtual bool create(double dt);
    virtual bool initialize(double dt);
    virtual bool advance(double dt);
    virtual bool reset(double dt);
    virtual bool cleanup();
    virtual bool stop();
    virtual bool preStop();
    virtual bool initializeFast(double dt);

};

} // namespace rocoma_example
