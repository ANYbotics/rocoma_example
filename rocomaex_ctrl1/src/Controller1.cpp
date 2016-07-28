#include "rocomaex_ctrl1/Controller1.hpp"
#include <pluginlib/class_list_macros.h>
#include "roco/controllers/adapters/ControllerAdapterInterface.hpp"
#include "rocoma/controllers/ControllerAdapter.hpp"

//using ctrll = rocoma::ControllerAdapter<rocomaex_ctrl1::Controller1, rocomaex_model::State, rocomaex_model::Command>;
//PLUGINLIB_EXPORT_CLASS(ctrll, roco::ControllerAdapterInterface)

namespace rocomaex_ctrl1 {

Controller1::Controller1(): Base("Controller1")
{
}

Controller1::Controller1(const std::string& controllerName): Base(controllerName)
{
}

Controller1::~Controller1()
{
}

bool Controller1::create(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

bool Controller1::initialize(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");
  return true;
}

bool Controller1::advance(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is advanced!");
  return true;
}

bool Controller1::reset(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is reset!");
  return true;
}

bool Controller1::cleanup()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is cleaned up!");
  return true;
}

bool Controller1::stop()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is stopped!");
  return true;
}

bool Controller1::preStop()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is pre-stopped!");
  return true;
}

}
