#pragma once

// rocomaex model
#include "rocomaex_model/State.hpp"
#include "rocomaex_model/Command.hpp"

// rocomaex controllers
#include "rocomaex_failproof_ctrl1/FailproofController1.hpp"
#include "rocomaex_ctrl1/Controller1.hpp"
#include "rocomaex_ctrl2/Controller2.hpp"
#include "rocomaex_emgcy_ctrl1/EmergencyController1.hpp"
#include "rocomaex_emgcy_ctrl2/EmergencyController2.hpp"

// rocoma
#include "rocoma/ControllerManager.hpp"
#include "rocoma/controllers/adapters.hpp"

// Boost
#include <boost/thread.hpp>

// Stl
#include <memory>

namespace rocoma_example {

class RocomaExample{
public:
  RocomaExample(const double timestep);
  virtual ~RocomaExample();

  virtual void init();
  virtual void cleanup();
  virtual bool update();

protected:
  using FpAdapter = rocoma::FailproofControllerAdapter< rocomaex_failproof_ctrl1::FailproofController1, rocomaex_model::State, rocomaex_model::Command >;
  using Emgcy1Adapter = rocoma::EmergencyControllerAdapter< rocomaex_emgcy_ctrl1::EmergencyController1, rocomaex_model::State, rocomaex_model::Command >;
  using Emgcy2Adapter = rocoma::EmergencyControllerAdapter< rocomaex_emgcy_ctrl2::EmergencyController2, rocomaex_model::State, rocomaex_model::Command >;
  using Ctrl1Adapter = rocoma::ControllerAdapter< rocomaex_ctrl1::Controller1, rocomaex_model::State, rocomaex_model::Command >;
  using Ctrl2Adapter = rocoma::ControllerAdapter< rocomaex_ctrl2::Controller2, rocomaex_model::State, rocomaex_model::Command >;

 private:
  rocoma::ControllerManager controllerManager_;
  std::shared_ptr<rocomaex_model::State> state_;
  std::shared_ptr<rocomaex_model::Command> command_;
  std::shared_ptr<boost::shared_mutex> mutexState_;
  std::shared_ptr<boost::shared_mutex> mutexCommand_;
};

}
