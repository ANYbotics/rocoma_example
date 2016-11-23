#include "rocoma_ros_example/RocomaRosExample.hpp"
#include "rocomaex_model/State.hpp"
#include "rocomaex_model/Command.hpp"

#include "message_logger/message_logger.hpp"

namespace rocoma_ros_example {

RocomaRosExample::RocomaRosExample(NodeHandlePtr nodeHandle):
      any_node::Node(nodeHandle),
      controllerManager_("rocomaex_model::State",
                         "rocomaex_model::Command")
{
}

RocomaRosExample::~RocomaRosExample()
{
}

void RocomaRosExample::init()
{
  std::shared_ptr<rocomaex_model::State> state(new rocomaex_model::State());
  std::shared_ptr<rocomaex_model::Command> command(new rocomaex_model::Command());
  std::shared_ptr<boost::shared_mutex> mutexState(new boost::shared_mutex());
  std::shared_ptr<boost::shared_mutex> mutexCommand(new boost::shared_mutex());

  // Initialize Controller Manager
  controllerManager_.setIsRealRobot(false);
  controllerManager_.setNodeHandle(this->getNodeHandle());
  controllerManager_.setTimestep(1);
  controllerManager_.setupControllersFromParameterServer( state,
                                                          command,
                                                          mutexState,
                                                          mutexCommand);
}

void RocomaRosExample::cleanup()
{
  controllerManager_.cleanup();
}

bool RocomaRosExample::update(const any_worker::WorkerEvent& event)
{
  controllerManager_.updateController();
  return true;
}

}
