/*
 * FailproofController.cpp
 *
 *  Created on: Jul 27, 2016
 *      Author: Gabriel Hottiger
 */

#include "rocomaex_failproof_ctrl/FailproofController.hpp"

namespace rocoma_example {

FailproofController::FailproofController()
:Base("FailproofController")
{

}

FailproofController::~FailproofController()
{

}

bool FailproofController::create(double dt)
{
  MELO_INFO_STREAM("Controller " << this->getName() << " is created!");
  return true;
}

void FailproofController::advance(double dt)
{
	MELO_INFO_STREAM("Controller " << this->getName() << " is advancing!");
}

bool FailproofController::cleanup() {
  MELO_INFO_STREAM("Controller " << this->getName() << " is beeing cleaned up!");
  return true;
}

} /* namespace rocoma_example */
