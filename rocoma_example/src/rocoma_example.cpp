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
  while(true) {
    boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(dt*1000));
    highlevelController.update();
    t.wait();
  }

  return 0;

}
