#pragma once

#include "any_node/Node.hpp"

#include "rocoma_ros/ControllerManagerRos.hpp"

#include "rocomaex_model/State.hpp"
#include "rocomaex_model/Command.hpp"

namespace rocoma_ros_example {

class RocomaRosExample: public any_node::Node {
public:
  RocomaRosExample() = delete;
  RocomaRosExample(NodeHandlePtr nodeHandle);
  ~RocomaRosExample();

  virtual void init();
  virtual void cleanup();
  virtual bool update(const any_worker::WorkerEvent& event);

 private:
  rocoma_ros::ControllerManagerRos<rocomaex_model::State, rocomaex_model::Command> controllerManager_;
};

}
