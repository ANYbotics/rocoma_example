// rocoma ros example
#include "rocoma_ros_example/RocomaRosExample.hpp"

// message logger
#include "message_logger/message_logger.hpp"

// parameter handler
#include <parameter_handler_ros/parameter_handler_ros.hpp>
#include <parameter_handler_std/parameter_handler_std.hpp>

namespace rocoma_ros_example {

RocomaRosExample::RocomaRosExample(NodeHandlePtr nodeHandle):
     any_node::Node(nodeHandle),
     timeStep_(0.01),
     controllerManager_("rocomaex_model::State",
                         "rocomaex_model::Command"),
     state_(new rocomaex_model::State()),
     command_(new rocomaex_model::Command()),
     mutexState_(new boost::shared_mutex()),
     mutexCommand_(new boost::shared_mutex()),
     vector3Param_ ("vector3Param",    Eigen::Vector3d{0.2,1.12,2.22},  Eigen::Vector3d{1.20,2.40,1.2340},  Eigen::Vector3d{100.9,50.2,200.2}),
     matrix3Param_ ("matrix3Param", Eigen::Matrix3d::Zero(), Eigen::Matrix3d::Zero(), Eigen::Matrix3d::Constant(100)),
     intParam_("intParam",0,0,20),
     matrixXParam_("matrixX", Eigen::MatrixXd::Ones(2,3), Eigen::MatrixXd::Zero(2,3), Eigen::MatrixXd::Constant(2,3,1900)),
     vectorXParam_("vectorX", Eigen::VectorXi::Ones(9), Eigen::VectorXi::Zero(9), Eigen::VectorXi::Constant(9,16)),
     intVector3Param_("intVector",    Eigen::Vector3i{0,1,2},  Eigen::Vector3i{0,0,0},  Eigen::Vector3i{100,50,200})
{
  doubleParam_.setName("doubleParam");
  doubleParam_.setValue(500.0);
  doubleParam_.setDefaultValue(500.0);
  doubleParam_.setMinValue(0.0);
  doubleParam_.setMaxValue(2000.00);
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


  //--- Configure parameter handler
  parameter_handler_ros::setParameterHandlerRos(this->getNodeHandle());

  parameter_handler::handler->addParam(doubleParam_);
  parameter_handler::handler->addParam(vector3Param_);
  parameter_handler::handler->addParam(matrix3Param_);
  parameter_handler::handler->addParam(intParam_);
  parameter_handler::handler->addParam(intVector3Param_);
  parameter_handler::handler->addParam(matrixXParam_);
  parameter_handler::handler->addParam(vectorXParam_);

}

bool RocomaRosExample::update(const any_worker::WorkerEvent& event)
{
  MELO_INFO_THROTTLE_STREAM(1.0, "Double: " << doubleParam_.getValue());
  MELO_INFO_THROTTLE_STREAM(1.0, "Vector: " << vector3Param_.getValue()(0) << " " << vector3Param_.getValue()(1) << " " << vector3Param_.getValue()(2));
  MELO_INFO_THROTTLE_STREAM(1.0, "M1: " << matrixXParam_.getValue()(0,0) << " " << matrixXParam_.getValue()(0,1) << " " << matrixXParam_.getValue()(0,2));
  MELO_INFO_THROTTLE_STREAM(1.0, "M2: " << matrixXParam_.getValue()(1,0) << " " << matrixXParam_.getValue()(1,1) << " " << matrixXParam_.getValue()(1,2));
  MELO_INFO_THROTTLE_STREAM(1.0, "V9: " << vectorXParam_.getValue()(0) << " " << vectorXParam_.getValue()(1) << " " << vectorXParam_.getValue()(2));

  //! Advance the controller manager.
  controllerManager_.updateController();
  return true;
}

void RocomaRosExample::cleanup()
{
  //! When done clean up the controller manager.
  controllerManager_.cleanup();
}

}
