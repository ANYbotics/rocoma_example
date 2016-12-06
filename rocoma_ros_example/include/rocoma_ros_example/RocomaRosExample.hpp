#pragma once

// any_node
#include "any_node/Node.hpp"

// rocoma ros
#include "rocoma_ros/ControllerManagerRos.hpp"

// rocomaex model
#include "rocomaex_model/State.hpp"
#include "rocomaex_model/Command.hpp"

// signal logger
#include <signal_logger/signal_logger.hpp>

#include <rosgraph_msgs/Clock.h>

namespace rocoma_ros_example {

/** This example shows how to setup a controller manager ros. To interact with the manager use the ros services
 *  provided by rocoma_ros::ControllerManagerRos.
 */
class RocomaRosExample: public any_node::Node {

public:
  enum class myTestEnum : int {
    NR1 = 0,
    NR2 = 1
  };

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

  bool saveLoggerData(std_srvs::TriggerRequest & req, std_srvs::TriggerResponse & res);
  bool publishWorker(const any_worker::WorkerEvent& event);


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

  //! Clock publisher
  ros::Publisher clockPublisher_;
  rosgraph_msgs::Clock time_;

  // Primitive types
  float myLogFloat_;
  double myLogDouble_;
  int myLogInt_;
  short myLogShort_;
  long myLogLong_;
  char myLogChar_;
  bool myLogBool_;
  signal_logger::TimestampPair myLogTimestamp_;

  // Eigen types
  signal_logger::Vector3d myLogVector3d_;
  signal_logger::MatrixXf myLogMatrixXf_;
  signal_logger::MatrixXd myLogMatrixXd_;
  signal_logger::MatrixXi myLogMatrixXi_;
  signal_logger::MatrixXs myLogMatrixXs_;
  signal_logger::MatrixXl myLogMatrixXl_;
  signal_logger::MatrixXc myLogMatrixXc_;
  signal_logger::MatrixXUc myLogMatrixXUc_;
  signal_logger::MatrixXb myLogMatrixXb_;

  // Kindr types
  signal_logger::KindrPositionD myLogPosition_;
  signal_logger::KindrRotationQuaternionD myLogQuaternion_;
  signal_logger::KindrEulerAnglesZyxD myLogEulerAngles_;
  signal_logger::KindrAngularVelocityD myLogAngularVelocity_;
  signal_logger::KindrAngleAxisD myLogAngleAxis_;
  signal_logger::KindrRotationMatrixD myLogRotationMatrix_;
  signal_logger::KindrRotationVectorD myLogRotationVector_;
  signal_logger::KindrLinearVelocityD myLogLinearVelocity_;
  signal_logger::KindrLinearAccelerationD myLogLinearAcceleration_;
  signal_logger::KindrAngularAccelerationD myLogAngularAcceleration_;
  signal_logger::KindrForceD myLogForce_;
  signal_logger::KindrTorqueD myLogTorque_;
  signal_logger::KindrVectorD myLogKindrVector_;
  Eigen::Matrix<float, 5, 8> myStrangeSizedMatrix_;
  myTestEnum myTestEnum_;
  signal_logger::KindrVectorAtPosition<signal_logger::KindrVectorD> myLogKindrVectorAtPosition_;

  ros::ServiceServer saveLoggerService_;
};

}
