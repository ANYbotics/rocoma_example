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

  while(i < (10/dt)) {
    boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(dt*1000));

    // Switch to walk after a second
    if(i == static_cast<unsigned int>(1/dt)) {
      highlevelController.walk();
    }

    // Call emergency stop after 4 seconds
    if(i == static_cast<unsigned int>(4/dt)) {
      highlevelController.emergencyStop();
    }

    // Call second emergency stop after 6 seconds
    if(i == static_cast<unsigned int>(6/dt)) {
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
