#include "rocomaex_ctrl2/Controller2.hpp"

namespace rocomaex_ctrl2 {

Controller2::Controller2(): Base("Controller2")
{
}

Controller2::Controller2(const std::string& controllerName): Base(controllerName)
{
}

Controller2::~Controller2()
{
}

bool Controller2::create(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

bool Controller2::initialize(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");
  return true;
}

bool Controller2::advance(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is advanced!");
  return true;
}

bool Controller2::reset(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is reset!");
  return true;
}

bool Controller2::cleanup()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is cleaned up!");
  return true;
}

bool Controller2::stop()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is stopped!");
  return true;
}

bool Controller2::preStop()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is pre-stopped!");
  return true;
}

}
