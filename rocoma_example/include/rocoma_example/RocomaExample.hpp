#pragma once

// rocomaex model
#include "rocomaex_model/RocoState.hpp"
#include "rocomaex_model/RocoCommand.hpp"

// rocoma
#include "rocoma/ControllerManager.hpp"

// Boost
#include <boost/thread.hpp>

// Stl
#include <memory>

namespace rocoma_example {

class RocomaExample{
public:

  //! Constructor
  RocomaExample(const double timestep);

  //! Destructor
  ~RocomaExample() = default;

  //! Initialize the example
  void init();

  //! Update the example
  void update();

  //! Cleanup the example
  void cleanup();

  //! Switch to walk
  void walk();

  //! Switch to grasp
  void grasp();

  //! Switch to standAndGrasp
  void standAndGrasp();

  //! Emergency stop
  void emergencyStop();

private:
  //! Time step determines update frequency
  double timeStep_;

  //! Controller manager
  rocoma::ControllerManager controllerManager_;

  //! Robot state
  std::shared_ptr<rocomaex_model::RocoState> state_;

  //! Actuator commands
  std::shared_ptr<rocomaex_model::RocoCommand> command_;

  //! Mutex for robot state
  std::shared_ptr<boost::shared_mutex> mutexState_;

  //! Mutex for actuator commands
  std::shared_ptr<boost::shared_mutex> mutexCommand_;
};

}
