// rocoma ros example
#include "rocoma_ros_example/RocomaRosExample.hpp"

// message logger
#include "message_logger/message_logger.hpp"

namespace rocoma_ros_example {

RocomaRosExample::RocomaRosExample(NodeHandlePtr nodeHandle):
     any_node::Node(nodeHandle),
     timeStep_(0.01),
     controllerManager_("rocomaex_model::State",
                         "rocomaex_model::Command"),
     state_(new rocomaex_model::State()),
     command_(new rocomaex_model::Command()),
     mutexState_(new boost::shared_mutex()),
     mutexCommand_(new boost::shared_mutex())
{
  // Populate data
  myLogFloat_ = 1.2;
  myLogDouble_ = 1.0;
  myLogInt_ = 99999;
  myLogShort_ = 3;
  myLogLong_ = 39;
  myLogChar_ = 'b';
  myLogBool_ = false;
  myLogTimestamp_ = signal_logger::TimestampPair(100, 23);

  myLogVector3d_ = Eigen::Vector3d(1.0,2.9,3.3);

  myLogMatrixXf_.resize(1,2);
  myLogMatrixXf_ << 23.4, 88.8;

  myLogMatrixXd_.resize(2,1);
  myLogMatrixXd_ << 4.2, 43.1;

  myLogMatrixXi_.resize(3,3);
  myLogMatrixXi_ << 1,2,3,
                    4,5,6,
                    7,8,9;
  myLogMatrixXs_.resize(2,2);
  myLogMatrixXs_ << 10,21,
                    34,25;
  myLogMatrixXl_.resize(1,3);
  myLogMatrixXl_ << 29 ,44, 12;

  myLogMatrixXc_.resize(1,1);
  myLogMatrixXc_ << 'u';

  myLogMatrixXUc_.resize(4,1);
  myLogMatrixXUc_ << 'o','k','o', 'k';

  myLogMatrixXb_.resize(1,2);
  myLogMatrixXb_<< true, false;

  myLogPosition_ = kindr::Position3D(1.3,3.2,5.5);
  myLogQuaternion_ = kindr::RotationQuaternionPD(1.0,0.0,0.0,0.0);
  myLogEulerAngles_ = kindr::EulerAnglesZyxPD(16.4,3.4,35);
  myTestEnum_ = myTestEnum::NR2;
  myLogAngularVelocity_ = kindr::LocalAngularVelocityPD(1.3,3.2,5.5);
}
}

RocomaRosExample::~RocomaRosExample()
{
}

void RocomaRosExample::init()
{
  /*** |--- EXAMPLE DESCRIPTION
   *   Let's assume a quadruped with an additional arm for manipulations. The quadruped can walk and grasp things,
   *   which are located on top of its torso. When walking fails or an emergency stop occurs it moves into a standing
   *   position. If the grasping task fails it moves the arm to a default configuration. It can also execute the tasks
   *   simultaneously, but does not know a proper reaction to a failure and thus freezes all the joints. There is also
   *   a mode for standing and grasping at the same time, to recover from failure the arm is set to default.
       ---|
   */

  /*** Initialize controller manager. If the default constructor of the manager was called,
   *   a sepereate init function has to be called in order to initialize the manager. This has
   *   to be done before adding controllers to the manager.
   */
  rocoma_ros::ControllerManagerRosOptions managerOptions;
  managerOptions.timeStep = timeStep_;
  managerOptions.isRealRobot = false;
  managerOptions.nodeHandle = this->getNodeHandle();
  controllerManager_.init(managerOptions);


  bool setupControllersInCode = true;

  if(setupControllersInCode) {
    //! Add controller pairs in code.

    //! The fail-proof controller is added by the plugin name
    std::string failproofControllerPluginName = "FailproofController1Plugin";

    //! --- Setup controller for walking, recovers to a standing position.
    rocoma_ros::ManagedControllerOptionsPair WalkToStand;

    /*** Walk controller (ros implementation)
     *   ControllerRos1Plugin is the ros implementation of Controller1Plugin. (see rocoma_example)
     */
    WalkToStand.first.pluginName_ = "ControllerRos1Plugin";
    WalkToStand.first.name_ = "WalkRos";
    WalkToStand.first.isRos_ = true;
    WalkToStand.first.parameterPath_ = "param/walk.xml";

    //! Stand controller
    WalkToStand.second.pluginName_ = "EmergencyController1Plugin";
    WalkToStand.second.name_ = "Stand";
    WalkToStand.second.isRos_ = false;
    WalkToStand.second.parameterPath_ = "param/stand.xml";

    //! ---


    //! --- Setup controller grasps and recovers to arm default position.
    rocoma_ros::ManagedControllerOptionsPair GraspToArmDefault;

    //! Grasp controller
    GraspToArmDefault.first.pluginName_ = "Controller2Plugin";
    GraspToArmDefault.first.name_ = "Grasp";
    GraspToArmDefault.first.isRos_ = false;
    GraspToArmDefault.first.parameterPath_ = "/home/user/parameters/grasp.txt";

    /*** Move arm to default controller (ros implementation)
     *   EmergencyControllerRos1Plugin is the ros implementation of EmergencyControllerPlugin2. (see rocoma_example)
     */
    GraspToArmDefault.second.pluginName_ = "EmergencyControllerRos1Plugin";
    GraspToArmDefault.second.name_ = "ArmDefaultRos";
    GraspToArmDefault.second.isRos_ = true;
    GraspToArmDefault.second.parameterPath_ = "armdefault.xml";

    //! ---


    //! --- Setup controller thats walks and grasps, without recovery behavior.
    rocoma_ros::ManagedControllerOptionsPair WalkAndGrasp;

    //! Walking controller
    WalkAndGrasp.first.pluginName_ = "Controller3Plugin";
    WalkAndGrasp.first.name_ = "WalkAndGrasp";
    WalkAndGrasp.first.isRos_ = false;
    WalkAndGrasp.first.parameterPath_ = "";

    //! No emergency controller -> use the failproof controller

    //! ---


    //! --- Setup controller thats stands and grasps, recovers to arm default.
    rocoma_ros::ManagedControllerOptionsPair StandAndGraspToArmDefault;

    //! Stand and Grasp controller
    StandAndGraspToArmDefault.first.pluginName_ = "Controller4Plugin";
    StandAndGraspToArmDefault.first.name_ = "StandAndGrasp";
    StandAndGraspToArmDefault.first.isRos_ = false;
    StandAndGraspToArmDefault.first.parameterPath_ = "";

    /*** Move arm to default controller (ros implementation)
     *   EmergencyControllerRos1Plugin is the ros implementation of EmergencyControllerPlugin2. (see rocoma_example)
     */
    StandAndGraspToArmDefault.second.pluginName_ = "EmergencyControllerRos1Plugin";
    StandAndGraspToArmDefault.second.name_ = "ArmDefaultRos";
    StandAndGraspToArmDefault.second.isRos_ = true;
    StandAndGraspToArmDefault.second.parameterPath_ = "armdefault.xml";

    //! ---

    // Build a vector from the defined controller pairs.
    std::vector<rocoma_ros::ManagedControllerOptionsPair> controllerPairs {WalkToStand, GraspToArmDefault, WalkAndGrasp, StandAndGraspToArmDefault};

    // Setup the controllers
    controllerManager_.setupControllers(failproofControllerPluginName, controllerPairs, state_, command_, mutexState_, mutexCommand_);
  }

  else {
      /** Setup the controllers via the rosparam server. See param/default_parameters.yaml to see how
       *  the controller pair details have to be loaded onto the rosparam server.
       */
      controllerManager_.setupControllersFromParameterServer( state_, command_, mutexState_, mutexCommand_);
  }


  // Add variables to std logger
  signal_logger::setSignalLoggerRos(&getNodeHandle());
  signal_logger::logger->initLogger(500, 5, "logging.yaml");


  signal_logger::add(myLogFloat_, "myFloat", "primitive_types", "-");
  signal_logger::add(myLogDouble_, "myDouble", "primitive_types", "-");
  signal_logger::add(myLogInt_, "myInt", "primitive_types", "-");
  signal_logger::add(myLogShort_, "myShort", "primitive_types", "-");
  signal_logger::add(myLogLong_, "myLong", "primitive_types", "-");
  signal_logger::add(myLogChar_, "myChar", "primitive_types", "-");
  signal_logger::add(myLogBool_, "myBool", "primitive_types", "-");
  signal_logger::add(myLogTimestamp_, "myTime", "primitive_types", "s/ns");

  signal_logger::add(myLogVector3d_, "myVector3", "eigen_types", "-");
  signal_logger::add(myLogMatrixXf_, "myFloatMatrix", "eigen_types", "-");
  signal_logger::add(myLogMatrixXd_, "myDoubleMatrix", "eigen_types", "-");
  signal_logger::add(myLogMatrixXs_, "myShortMatrix", "eigen_types", "-");
  signal_logger::add(myLogMatrixXi_, "myIntMatrix", "eigen_types", "-");
  signal_logger::add(myLogMatrixXl_, "myLongMatrix", "eigen_types", "-");
  signal_logger::add(myLogMatrixXc_, "myCharMatrix", "eigen_types", "-");
  signal_logger::add(myLogMatrixXUc_, "myUnsignedCharMatrix", "eigen_types", "-");
  signal_logger::add(myLogMatrixXb_, "myBoolMatrix", "eigen_types", "-");

  signal_logger::add(myLogPosition_, "myPosition", "kindr_types", "m");
  signal_logger::add(myLogQuaternion_, "myQuaternion", "kindr_types", "-");
  signal_logger::add(myLogEulerAngles_, "myEulerAngles", "kindr_types", "rad");
  signal_logger::add(myLogAngularVelocity_, "myAngularVelocity", "kindr_types", "rad/s");
  signal_logger::add(myLogAngleAxis_, "myAngleAxis", "kindr_types", "-");
  signal_logger::add(myLogRotationMatrix_, "myRotationMatrix", "kindr_types", "-");
  signal_logger::add(myLogRotationVector_, "myRotationVector", "kindr_types", "-");
  signal_logger::add(myLogLinearVelocity_, "myLinearVelocity", "kindr_types", "m/s");
  signal_logger::add(myLogLinearAcceleration_, "myLinearAcceleration", "kindr_types", "m/(s*s)");
  signal_logger::add(myLogAngularAcceleration_, "myAngularAcceleration", "kindr_types", "rad/(s*s)");
  signal_logger::add(myLogTorque_, "myTorque", "kindr_types", "Nm");
  signal_logger::add(myLogKindrVector_, "myKindrVector", "kindr_types", "-");
  signal_logger::add(myLogForce_, "myForce", "kindr_types", "N");
  signal_logger::add(myStrangeSizedMatrix_, "myStrangesizedType", "eigen_types", "N");
  signal_logger::add(myTestEnum_, "myEnum", "enum_types", "");


  myLogKindrVectorAtPosition_.vectorFrame = "world";
  myLogKindrVectorAtPosition_.positionFrame = "base";
  signal_logger::add(myLogKindrVectorAtPosition_, "myKindrVectorAtPosition", "kindr_types", "-");

  signal_logger::logger->updateLogger();
  signal_logger::logger->startLogger();

  // Publish data in different thread
  any_worker::WorkerOptions options;
  options.callback_ = std::bind(&RocomaExample::publishWorker, this, std::placeholders::_1);
  options.name_ = "publishLoggerData";
  options.timeStep_ = 0.05;
  this->addWorker(options);

}

bool RocomaRosExample::update(const any_worker::WorkerEvent& event)
{
  //! Advance the controller manager.
  controllerManager_.updateController();
  return true;
}

void RocomaRosExample::cleanup()
{
  //! When done clean up the controller manager.
  controllerManager_.cleanup();
}


bool RocomaExample::saveLoggerData(std_srvs::TriggerRequest & req, std_srvs::TriggerResponse & res) {
  signal_logger::logger->saveLoggerData();
  return true;
}

bool RocomaExample::publishWorker(const any_worker::WorkerEvent& event) {
  return signal_logger::logger->publishData();
}

}
