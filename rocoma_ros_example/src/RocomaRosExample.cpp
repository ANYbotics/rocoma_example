#include "rocoma_ros_example/RocomaRosExample.hpp"
#include "rocomaex_model/State.hpp"
#include "rocomaex_model/Command.hpp"

#include "message_logger/message_logger.hpp"

namespace rocoma_ros_example {

RocomaRosExample::RocomaRosExample(NodeHandlePtr nodeHandle):
          any_node::Node(nodeHandle),
          controllerManager_("rocomaex_model::State",
                             "rocomaex_model::Command"),
                             state_(new rocomaex_model::State()),
                             command_(new rocomaex_model::Command()),
                             mutexState_(new boost::shared_mutex()),
                             mutexCommand_(new boost::shared_mutex())
{
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
  managerOptions.timeStep = 1.0;
  managerOptions.isRealRobot = false;
  managerOptions.nodeHandle = this->getNodeHandle();
  controllerManager_.init(managerOptions);


  bool setupControllersInCode = true;

  if(setupControllersInCode) {
    //! Add controllers pairs

    //! ControllerRosPlugin1 is the ros implementation of Controller1 -> the normal walk controller from rocoma_example.
    rocoma_ros::ManagedControllerOptionsPair WalkToStand;
    WalkToStand.first.pluginName_ = "ControllerRos1Plugin";
    WalkToStand.first.name_ = "WalkRos";
    WalkToStand.first.isRos_ = true;
    WalkToStand.first.parameterPath_ = "param/walk.xml";

    WalkToStand.second.pluginName_ = "EmergencyController1Plugin";
    WalkToStand.second.name_ = "Stand";
    WalkToStand.second.isRos_ = false;
    WalkToStand.second.parameterPath_ = "param/stand.xml";

    //! EmergencyControllerRos1Plugin is the ros implementation of EmergencyController1 -> the arm default controller from rocoma_example.
    rocoma_ros::ManagedControllerOptionsPair GraspToArmDefault;
    GraspToArmDefault.first.pluginName_ = "Controller2Plugin";
    GraspToArmDefault.first.name_ = "Grasp";
    GraspToArmDefault.first.isRos_ = false;
    GraspToArmDefault.first.parameterPath_ = "/home/user/parameters/grasp.txt";

    GraspToArmDefault.second.pluginName_ = "EmergencyControllerRos1Plugin";
    GraspToArmDefault.second.name_ = "ArmDefaultRos";
    GraspToArmDefault.second.isRos_ = true;
    GraspToArmDefault.second.parameterPath_ = "armdefault.xml";

    rocoma_ros::ManagedControllerOptionsPair WalkAndGrasp;
    WalkAndGrasp.first.pluginName_ = "Controller3Plugin";
    WalkAndGrasp.first.name_ = "WalkAndGrasp";
    WalkAndGrasp.first.isRos_ = false;
    WalkAndGrasp.first.parameterPath_ = "";
    // No emergency controller can not recover

    rocoma_ros::ManagedControllerOptionsPair StandAndGraspToArmDefault;
    StandAndGraspToArmDefault.first.pluginName_ = "Controller4Plugin";
    StandAndGraspToArmDefault.first.name_ = "StandAndGrasp";
    StandAndGraspToArmDefault.first.isRos_ = false;
    StandAndGraspToArmDefault.first.parameterPath_ = "";

    StandAndGraspToArmDefault.second.pluginName_ = "EmergencyControllerRos1Plugin";
    StandAndGraspToArmDefault.second.name_ = "ArmDefaultRos";
    StandAndGraspToArmDefault.second.isRos_ = true;
    StandAndGraspToArmDefault.second.parameterPath_ = "armdefault.xml";

    std::vector<rocoma_ros::ManagedControllerOptionsPair> controllerPairs {WalkToStand, GraspToArmDefault, WalkAndGrasp, StandAndGraspToArmDefault};

    controllerManager_.setupControllers("FailproofController1Plugin", controllerPairs, state_, command_, mutexState_, mutexCommand_);
  }

  else {
      /** Setup the controllers via the rosparam server. See param/default_parameters.yaml to see how
       *  the controller pair details have to be loaded onto the rosparam server.
       */
      controllerManager_.setupControllersFromParameterServer( state_, command_, mutexState_, mutexCommand_);
  }

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
