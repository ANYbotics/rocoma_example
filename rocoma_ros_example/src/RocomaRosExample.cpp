// rocoma ros example
#include "rocoma_ros_example/RocomaRosExample.hpp"

// message logger
#include "message_logger/message_logger.hpp"

namespace rocoma_ros_example {

RocomaRosExample::RocomaRosExample(NodeHandlePtr nodeHandle):
     any_node::Node(nodeHandle),
     timeStep_(0.01),
     controllerManager_("rocomaex_model::RocoState",
                        "rocomaex_model::RocoCommand"),
     state_(new rocomaex_model::RocoState()),
     command_(new rocomaex_model::RocoCommand()),
     mutexState_(new boost::shared_mutex()),
     mutexCommand_(new boost::shared_mutex())
{
}

bool RocomaRosExample::init()
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
    std::string failproofControllerPluginName = "FailproofController1";


    std::vector<rocoma_ros::ManagedModuleOptions> sharedModuleOptions(1);
    sharedModuleOptions.at(0).pluginName_ = "MySharedModule";
    sharedModuleOptions.at(0).name_ = "MySharedModule";
    sharedModuleOptions.at(0).parameterPath_ = "";
    sharedModuleOptions.at(0).isRos_ = false;
    if(!controllerManager_.setupSharedModules(sharedModuleOptions)) {
      return false;
    }

    //! --- Setup controller for walking, recovers to a standing position.
    rocoma_ros::ManagedControllerOptionsPair WalkToStand;

    /*** Walk controller (ros implementation)
     *   ControllerRos1Plugin is the ros implementation of Controller1Plugin. (see rocoma_example)
     */
    WalkToStand.first.pluginName_ = "ControllerRos1";
    WalkToStand.first.name_ = "WalkRos";
    WalkToStand.first.isRos_ = true;
    WalkToStand.first.parameterPath_ = "param/walk.xml";

    //! Stand controller
    WalkToStand.second.pluginName_ = "EmergencyController1";
    WalkToStand.second.name_ = "Stand";
    WalkToStand.second.isRos_ = false;
    WalkToStand.second.parameterPath_ = "param/stand.xml";

    //! ---


    //! --- Setup controller grasps and recovers to arm default position.
    rocoma_ros::ManagedControllerOptionsPair GraspToArmDefault;

    //! Grasp controller
    GraspToArmDefault.first.pluginName_ = "Controller2";
    GraspToArmDefault.first.name_ = "Grasp";
    GraspToArmDefault.first.isRos_ = false;
    GraspToArmDefault.first.parameterPath_ = "/home/user/parameters/grasp.txt";
    GraspToArmDefault.first.sharedModuleNames_ = {"MySharedModule"};

    /*** Move arm to default controller (ros implementation)
     *   EmergencyControllerRos1Plugin is the ros implementation of EmergencyControllerPlugin2. (see rocoma_example)
     */
    GraspToArmDefault.second.pluginName_ = "EmergencyControllerRos1";
    GraspToArmDefault.second.name_ = "ArmDefaultRos";
    GraspToArmDefault.second.isRos_ = true;
    GraspToArmDefault.second.parameterPath_ = "armdefault.xml";

    //! ---


    //! --- Setup controller thats walks and grasps, without recovery behavior.
    rocoma_ros::ManagedControllerOptionsPair WalkAndGrasp;

    //! Walking controller
    WalkAndGrasp.first.pluginName_ = "Controller3";
    WalkAndGrasp.first.name_ = "WalkAndGrasp";
    WalkAndGrasp.first.isRos_ = false;
    WalkAndGrasp.first.parameterPath_ = "";

    //! No emergency controller -> use the failproof controller

    //! ---


    //! --- Setup controller thats stands and grasps, recovers to arm default.
    rocoma_ros::ManagedControllerOptionsPair StandAndGraspToArmDefault;

    //! Stand and Grasp controller
    StandAndGraspToArmDefault.first.pluginName_ = "Controller4";
    StandAndGraspToArmDefault.first.name_ = "StandAndGrasp";
    StandAndGraspToArmDefault.first.isRos_ = false;
    StandAndGraspToArmDefault.first.parameterPath_ = "";
    StandAndGraspToArmDefault.first.sharedModuleNames_ = {"MySharedModule"};


    /*** Move arm to default controller (ros implementation)
     *   EmergencyControllerRos1Plugin is the ros implementation of EmergencyControllerPlugin2. (see rocoma_example)
     */
    StandAndGraspToArmDefault.second.pluginName_ = "EmergencyControllerRos1";
    StandAndGraspToArmDefault.second.name_ = "ArmDefaultRos";
    StandAndGraspToArmDefault.second.isRos_ = true;
    StandAndGraspToArmDefault.second.parameterPath_ = "armdefault.xml";

    //! ---

    // Build a vector from the defined controller pairs.
    std::vector<rocoma_ros::ManagedControllerOptionsPair> controllerPairs {WalkToStand, GraspToArmDefault, WalkAndGrasp, StandAndGraspToArmDefault};

    // Setup the controllers
    if(!controllerManager_.setupControllers(failproofControllerPluginName, controllerPairs, state_, command_, mutexState_, mutexCommand_)) {
      return false;
    }
  }

  else {
      /** Setup the controllers via the rosparam server. See param/default_parameters.yaml to see how
       *  the controller pair details have to be loaded onto the rosparam server.
       */
      if(!controllerManager_.setupControllersFromParameterServer( state_, command_, mutexState_, mutexCommand_)) {
        return false;
      }
  }

  return true;
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

}
