#include "rocomaex_emgcy_ctrl1/EmergencyController1.hpp"

namespace rocomaex_emgcy_ctrl1 {

EmergencyController1::EmergencyController1(): Base()
{
}

EmergencyController1::~EmergencyController1()
{
}

bool EmergencyController1::create(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

bool EmergencyController1::initialize(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");
  return true;
}

bool EmergencyController1::advance(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is advanced!");
  return true;
}

bool EmergencyController1::reset(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is reset!");
  return true;
}

bool EmergencyController1::cleanup()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is cleaned up!");
  return true;
}

bool EmergencyController1::stop()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is stopped!");
  return true;
}

bool EmergencyController1::preStop()
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is pre-stopped!");
  return true;
}

bool EmergencyController1::initializeFast(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is initialized!");
  return true;
}

}
