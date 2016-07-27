#include "rocoma_example/RocomaExample.hpp"

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
