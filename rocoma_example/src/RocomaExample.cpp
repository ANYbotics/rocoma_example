#include "rocoma_example/RocomaExample.hpp"
#include "rocomaex_model/State.hpp"
#include "rocomaex_model/Command.hpp"
//s#include "rocomaex_ctrl1/Controller1.hpp"

#include "message_logger/message_logger.hpp"

namespace rocoma_example {

RocomaExample::RocomaExample(NodeHandlePtr nodeHandle):
    any_node::Node(nodeHandle),
    controllerManager_(*nodeHandle)
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
  //srocoma::ControllerAdapter<rocomaex_ctrl1::Controller1, rocomaex_model::State, rocomaex_model::Command> a();
  controllerManager_.addController<rocomaex_model::State, rocomaex_model::Command>("rocomaex_ctrl1",
                                                                                   "rocomaex_ctrl1",
                                                                                   "Controller1",
                                                                                   0.01,
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
  return true;
}

}
