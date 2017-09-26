// rocoma example
#include "rocoma_example/RocomaExample.hpp"

// boost
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// Timestep
double dt = 0.01;

// Init highlevel controller at a 100 Hz
rocoma_example::RocomaExample highlevelController(dt);

void signalHandler( int signum )
{
  highlevelController.cleanup();
  exit(signum);
}

int main(int argc, char **argv)
{
  // register signal SIGINT and signal handler
  signal(SIGINT, signalHandler);

  // init highlevel controller
  highlevelController.init();

  // update controller with given timestep
  boost::asio::io_service io;
  unsigned int i = 0;

  while(i < (30/dt)) {
    boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(dt*1000));

    // Switch to walk after a second
    if(i == static_cast<unsigned int>(1/dt)) {
      highlevelController.walk();
    }

    // Switch to grasp after 8 seconds
    if(i == static_cast<unsigned int>(8/dt)) {
      highlevelController.grasp();
    }

    // Call emergency stop after 12 seconds
    if(i == static_cast<unsigned int>(12/dt)) {
      highlevelController.emergencyStop();
    }

    // Switch to standAndGrasp after 16 seconds
    if(i == static_cast<unsigned int>(16/dt)) {
      highlevelController.standAndGrasp();
    }

    // Call emergency stop after 22 seconds
    if(i == static_cast<unsigned int>(22/dt)) {
      highlevelController.emergencyStop();
    }

    // Call second emergency stop after 25 seconds
    if(i == static_cast<unsigned int>(25/dt)) {
      highlevelController.emergencyStop();
    }

    // Update controller
    highlevelController.update();

    // Wait for timer
    t.wait();

    // Iterate
    i++;
  }

  highlevelController.cleanup();

  return 0;

}
