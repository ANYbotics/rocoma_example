// rocoma example
#include "rocoma_example/RocomaExample.hpp"

// rocomaex controllers
#include "rocomaex_failproof_ctrl1/FailproofController1.hpp"
#include "rocomaex_ctrl1/Controller1.hpp"
#include "rocomaex_ctrl2/Controller2.hpp"
#include "rocomaex_emgcy_ctrl1/EmergencyController1.hpp"
#include "rocomaex_emgcy_ctrl2/EmergencyController2.hpp"

// message logger
#include "message_logger/message_logger.hpp"

namespace rocoma_example {

RocomaExample::RocomaExample(const double timeStep):
      controllerManager_(timeStep),
			state_(new rocomaex_model::State()),
			command_(new rocomaex_model::Command()),
			mutexState_(new boost::shared_mutex()),
			mutexCommand_(new boost::shared_mutex())
{
}

RocomaExample::~RocomaExample()
{
}

void RocomaExample::init()
{
  // convinience
  using FailproofControllerPtr = rocoma::ControllerManager::FailproofControllerPtr;
  using EmgcyControllerPtr = rocoma::ControllerManager::EmgcyControllerPtr;
  using ControllerPtr = rocoma::ControllerManager::ControllerPtr;

  // Setup failproof controller
  FpAdapter* failproof = new FpAdapter();
  failproof->setName("Shutoff");
  failproof->setStateAndCommand(state_, mutexState_, command_, mutexCommand_);
  failproof->setParameterPath("parameter.xml");

  // Setup first emergency controller
  Emgcy1Adapter* emgcy_ctrl1 = new Emgcy1Adapter();
  emgcy_ctrl1->setName("Recover");
  emgcy_ctrl1->setStateAndCommand(state_, mutexState_, command_, mutexCommand_);
  emgcy_ctrl1->setParameterPath("emgcy_parameters.xml");

  // Setup first controller
  Ctrl1Adapter* ctrl1 = new Ctrl1Adapter();
  ctrl1->setName("DoFancyStuff");
  ctrl1->setStateAndCommand(state_, mutexState_, command_, mutexCommand_);
  ctrl1->setParameterPath("emgcy_parameters.xml");

  // Setup second controller
  Ctrl2Adapter* ctrl2 = new Ctrl2Adapter();
  ctrl2->setName("DoStuff");
  ctrl2->setStateAndCommand(state_, mutexState_, command_, mutexCommand_);
  ctrl2->setParameterPath("emgcy_parameters.xml");


  // Make pairs
  controllerManager_.setFailproofController(FailproofControllerPtr(failproof));
  controllerManager_.addControllerPair(ControllerPtr(ctrl1), EmgcyControllerPtr(emgcy_ctrl1));
  controllerManager_.addControllerPairWithExistingEmergencyController(ControllerPtr(ctrl2), "Recover");

  // These controllers are now owned by the controller manager
//  controllerManager_.addControllerPair(std::move(controller2), std::move(emergency3));

  // Initialize Controller Manager
  controllerManager_.setIsRealRobot(false);
  controllerManager_.setTimestep(1);
}

void RocomaExample::cleanup()
{
  controllerManager_.cleanup();
}

bool RocomaExample::update()
{
  controllerManager_.updateController();
  return true;
}

}
