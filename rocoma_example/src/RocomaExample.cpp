// rocoma example
#include "rocoma_example/RocomaExample.hpp"

// rocoma
#include "rocoma/controllers/adapters.hpp"

// rocomaex controllers
#include "rocomaex_failproof_ctrl1/FailproofController1.hpp"
#include "rocomaex_ctrl1/Controller1.hpp"
#include "rocomaex_ctrl2/Controller2.hpp"
#include "rocomaex_emgcy_ctrl1/EmergencyController1.hpp"
#include "rocomaex_emgcy_ctrl2/EmergencyController2.hpp"

// roco
#include "roco/controllers/controllers.hpp"

// message logger
#include "message_logger/message_logger.hpp"

namespace rocoma_example {

RocomaExample::RocomaExample(const double timeStep):
      timeStep_(timeStep),
      controllerManager_(),
      state_(new rocomaex_model::RocoState()),
      command_(new rocomaex_model::RocoCommand()),
      mutexState_(new boost::shared_mutex()),
      mutexCommand_(new boost::shared_mutex())
{
}

void RocomaExample::init()
{
  /*** |--- EXAMPLE DESCRIPTION
   *   Let's assume a quadruped with an additional arm for manipulations. The quadruped can walk and grasp things,
   *   which are located on top of its torso. When walking fails or an emergency stop occurs it moves into a standing
   *   position. If the grasping task fails it moves the arm to a default configuration. It can also execute the tasks
   *   simultaneously, but does not know a proper reaction to a failure and thus freezes all the joints. There is also
   *   a mode for standing and grasping at the same time, to recover from failure the arm is set to default.
       ---|
   */


  /*** The controller adapter type names are quite long. For convenience one can define typedefs that
   *   correspond to the used controller adapters. Note the last controller, which is a tuple type.
   *   This type allows to pair an arbitrary number of controllers to a single controller tuple, in which
   *   the controllers are executed in series (same order as in type specification).
   */
  using FreezeCtrl = rocoma::FailproofControllerAdapter< rocomaex_failproof_ctrl1::FailproofController1, rocomaex_model::RocoState, rocomaex_model::RocoCommand >;
  using StandCtrl = rocoma::EmergencyControllerAdapter< rocomaex_emgcy_ctrl1::EmergencyController1, rocomaex_model::RocoState, rocomaex_model::RocoCommand >;
  using ArmDefaultCtrl = rocoma::EmergencyControllerAdapter< rocomaex_emgcy_ctrl2::EmergencyController2, rocomaex_model::RocoState, rocomaex_model::RocoCommand >;
  using WalkCtrl = rocoma::ControllerAdapter< rocomaex_ctrl1::Controller1, rocomaex_model::RocoState, rocomaex_model::RocoCommand >;
  using GraspCtrl = rocoma::ControllerAdapter< rocomaex_ctrl2::Controller2, rocomaex_model::RocoState, rocomaex_model::RocoCommand >;
  using GraspAndWalkTuple = roco::ControllerTuple<rocomaex_model::RocoState, rocomaex_model::RocoCommand, rocomaex_ctrl1::Controller1, rocomaex_ctrl2::Controller2>;
  using GraspAndWalkCtrl = rocoma::ControllerAdapter< GraspAndWalkTuple, rocomaex_model::RocoState, rocomaex_model::RocoCommand >;
  using GraspAndStandTuple = roco::ControllerTuple<rocomaex_model::RocoState, rocomaex_model::RocoCommand, rocomaex_emgcy_ctrl1::EmergencyController1, rocomaex_ctrl2::Controller2>;
  using GraspAndStandCtrl = rocoma::ControllerAdapter< GraspAndStandTuple, rocomaex_model::RocoState, rocomaex_model::RocoCommand >;

  /*** Controllers usually have a default name, use setName to override the default name. The same holds for the parameter
   *   path (set to non-sense in this example). The path is an absolute path or relative path to the current directory at execution time.
   *   Since the controller manager only knows the controller by it's interface and we are using the roco::Controller class
   *   in all of our controllers, we have to specify state and command and their corresponding mutexes before adding the
   *   controller to the manager.
   */

  /*** Setup a fail-proof controller that freezes all joints. This controller is absolutely necessary
   *   for the controller manager to be executed. We use a unique_ptr to indicate the ownership of the controller.
   */
  std::unique_ptr<FreezeCtrl> freeze(new FreezeCtrl());
  freeze->setName("Freeze");
  freeze->setParameterPath("");
  freeze->setStateAndCommand(state_, mutexState_, command_, mutexCommand_);

  //--- Setup all emergency controllers. Again we use a unique_ptr to indicate the ownership of the controller.

  //! Shared module
  roco::SharedModulePtr shared_module(new rocomaex_model::MySharedModule());
  shared_module->setName("MySharedModule");
  shared_module->setParameterPath("");

  //! Setup a controller that brings the quadruped into a standing position.
  std::unique_ptr<StandCtrl> stand(new StandCtrl());
  stand->setName("Stand");
  stand->setStateAndCommand(state_, mutexState_, command_, mutexCommand_);
  stand->setParameterPath("stand.yaml");

  //! Setup a controller that resets the arm to a default configuration.
  std::unique_ptr<ArmDefaultCtrl> arm2Default(new ArmDefaultCtrl());
  arm2Default->setName("ArmDefault");
  arm2Default->setStateAndCommand(state_, mutexState_, command_, mutexCommand_);
  arm2Default->setParameterPath("/home/user/params/armdefault.txt");

  // ---

  //--- Setup all controllers. Again we use a unique_ptr to indicate the ownership of the controller.

  //! Setup controller that enables quadruped to walk.
  std::unique_ptr<WalkCtrl> walk(new WalkCtrl());
  walk->setName("Walk");
  walk->setStateAndCommand(state_, mutexState_, command_, mutexCommand_);
  walk->setParameterPath("param/walk/parameters.xml");

  //! Setup controller that grasps things located on the quadruped's torso.
  std::unique_ptr<GraspCtrl> grasp(new GraspCtrl());
  grasp->setName("Grasp");
  grasp->setStateAndCommand(state_, mutexState_, command_, mutexCommand_);
  grasp->setParameterPath("param/grasp.txt");
  grasp->addControllerSharedModule(shared_module);

  //! Setup controller that combines the grasping and walking task.
  std::unique_ptr<GraspAndWalkCtrl> graspAndWalk(new GraspAndWalkCtrl());
  graspAndWalk->setName("WalkAndGrasp");
  graspAndWalk->setStateAndCommand(state_, mutexState_, command_, mutexCommand_);
  graspAndWalk->setParameterPath("walkAndGrasp.xml");

  //! Setup controller that combines the grasping and standing task.
  std::unique_ptr<GraspAndStandCtrl> graspAndStand(new GraspAndStandCtrl());
  graspAndStand->setName("StandAndGrasp");
  graspAndStand->setStateAndCommand(state_, mutexState_, command_, mutexCommand_);
  graspAndStand->setParameterPath("standAndGrasp.yaml");
  graspAndStand->addControllerSharedModule(shared_module);
  // ---

  /*** Initialize controller manager. If the default constructor of the manager was called,
   *   a sepereate init function has to be called in order to initialize the manager. This has
   *   to be done before adding controllers to the manager.
   */
  rocoma::ControllerManagerOptions managerOptions;
  managerOptions.isRealRobot = false;
  managerOptions.timeStep = timeStep_;
  controllerManager_.init(managerOptions);
  controllerManager_.addSharedModule(std::move(shared_module));

  /*** Now the controllers can be added to the manager. Controllers must have unique names.
   *   However, multiple instances of the same controller with a different name can be added.
   *   Emergency controllers can be shared among different controllers. Only one fail-proof controller
   *   can be added. Use std::move() to transfer the ownership to the controllermanager.
   */
  controllerManager_.setFailproofController(std::move(freeze));
  controllerManager_.addControllerPair(std::move(walk), std::move(stand));
  controllerManager_.addControllerPair(std::move(grasp), std::move(arm2Default));
  controllerManager_.addControllerPair(std::move(graspAndWalk), nullptr);
  controllerManager_.addControllerPairWithExistingEmergencyController(std::move(graspAndStand), "ArmDefault");

  //! After the move operation all controllers are invalidated and set to the nullptr.
}

void RocomaExample::update()
{
  //! Advance the controller manager with the given timestep.
  controllerManager_.updateController();
}

void RocomaExample::cleanup()
{
  //! When done clean up the controller manager.
  controllerManager_.cleanup();
}

void RocomaExample::walk()
{
  //! Switch to the walking controller
  controllerManager_.switchController("Walk");
}

void RocomaExample::grasp()
{
  //! Switch to the walking controller
  controllerManager_.switchController("Grasp");
}

void RocomaExample::standAndGrasp()
{
  //! Switch to the walking controller
  controllerManager_.switchController("StandAndGrasp");
}

void RocomaExample::emergencyStop()
{
  //! Trigger an emergency stop
  controllerManager_.emergencyStop();
}

}
