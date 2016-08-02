#include "rocoma_example/RocomaExample.hpp"
#include "rocomaex_model/State.hpp"
#include "rocomaex_model/Command.hpp"
#include "rocomaex_ctrl1/Controller1.hpp"

#include "message_logger/message_logger.hpp"

namespace rocoma_example {

RocomaExample::RocomaExample(NodeHandlePtr nodeHandle):
        any_node::Node(nodeHandle),
        controllerManager_(*nodeHandle,"rocomaex_model::State",
        "rocomaex_model::Command")
{
}

RocomaExample::~RocomaExample()
{
}

void RocomaExample::init()
{
  std::shared_ptr<rocomaex_model::State> state(new rocomaex_model::State());
  std::shared_ptr<rocomaex_model::Command> command(new rocomaex_model::Command());
  std::shared_ptr<boost::shared_mutex> mutexState(new boost::shared_mutex());
  std::shared_ptr<boost::shared_mutex> mutexCommand(new boost::shared_mutex());
  std::shared_ptr<any_worker::WorkerManager> workerManager(new any_worker::WorkerManager());

  std::vector<std::string> controllerNames {"Controller1Plugin", "Controller2Plugin", "Controller3Plugin"};
  std::vector<std::string> emergencyControllerNames {"EmergencyController1Plugin", "EmergencyController2Plugin"};
  std::string failproofControllerName {"FailproofController1Plugin"};

  controllerManager_.setupControllers(failproofControllerName,
                                      emergencyControllerNames,
                                      controllerNames,
                                      state,
                                      command,
                                      mutexState,
                                      mutexCommand,
                                      workerManager);

}

void RocomaExample::cleanup()
{
}

bool RocomaExample::update(const any_worker::WorkerEvent& event)
{
  MELO_WARN("UPDATING!");
  controllerManager_.updateController();
  return true;
}

}
