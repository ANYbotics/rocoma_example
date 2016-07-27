#include "rocomaex_emgcy_ctrl2/EmergencyController2.hpp"

namespace rocoma_example {

EmergencyController2::EmergencyController2(): Base("EmergencyController2")
{
}

EmergencyController2::EmergencyController2(const std::string& controllerName): Base(controllerName)
{
}

EmergencyController2::~EmergencyController2()
{
}

bool EmergencyController2::create(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

bool EmergencyController2::initialize(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");
  return true;
}

bool EmergencyController2::advance(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is advanced!");
  return true;
}

bool EmergencyController2::reset(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is reset!");
  return true;
}

bool EmergencyController2::cleanup()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is cleaned up!");
  return true;
}

bool EmergencyController2::stop()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is stopped!");
  return true;
}

bool EmergencyController2::preStop()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is pre-stopped!");
  return true;
}

bool EmergencyController2::initializeFast(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");
  return true;
}

}
