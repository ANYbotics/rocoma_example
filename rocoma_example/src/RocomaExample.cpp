#include "rocoma_example/RocomaExample.hpp"
#include "rocomaex_ctrl1/Controller1.hpp"
#include "rocomaex_model/State.hpp"
#include "rocomaex_model/Command.hpp"

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
  rocoma::ControllerAdapter<rocomaex_ctrl1::Controller1, rocomaex_model::State, rocomaex_model::Command> c;
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
