#pragma once

// any_node
#include "any_node/Node.hpp"

// rocoma ros
#include "rocoma_ros/ControllerManagerRos.hpp"

// rocomaex model
#include "rocomaex_model/State.hpp"
#include "rocomaex_model/Command.hpp"

#include <parameter_handler/Parameter.hpp>

namespace rocoma_ros_example {

/** This example shows how to setup a controller manager ros. To interact with the manager use the ros services
 *  provided by rocoma_ros::ControllerManagerRos.
 */
class RocomaRosExample: public any_node::Node {
public:
  //! Delete default constructor
  RocomaRosExample() = delete;

  //! Constructor
  RocomaRosExample(NodeHandlePtr nodeHandle);

  //! Destructor
  ~RocomaRosExample();

  //! Init the ros example
  virtual void init();

  //! Update the ros example
  virtual bool update(const any_worker::WorkerEvent& event);

  //! Cleanup the ros example
  virtual void cleanup();

 private:
  //! Time step determines update frequency
  double timeStep_;

  //! Controller manager ros
  rocoma_ros::ControllerManagerRos<rocomaex_model::State, rocomaex_model::Command> controllerManager_;

  //! Robot state
  std::shared_ptr<rocomaex_model::State> state_;

  //! Actuator commands
  std::shared_ptr<rocomaex_model::Command> command_;

  //! Mutex for robot state
  std::shared_ptr<boost::shared_mutex> mutexState_;

  //! Mutex for actuator commands
  std::shared_ptr<boost::shared_mutex> mutexCommand_;

  parameter_handler::Parameter<double> doubleParam_;
  parameter_handler::Parameter<Eigen::Vector3d> vector3Param_;
  parameter_handler::Parameter<Eigen::Matrix3d> matrix3Param_;
  parameter_handler::Parameter<Eigen::MatrixXd> matrixXParam_;
  parameter_handler::Parameter<Eigen::VectorXi> vectorXParam_;
  parameter_handler::Parameter<int> intParam_;
  parameter_handler::Parameter<Eigen::Vector3i> intVector3Param_;
};

}
