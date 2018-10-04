// rocoma example
#include "rocoma_ros_example/RocomaRosExample.hpp"

// nodewrap
#include "any_node/Nodewrap.hpp"


int main(int argc, char **argv)
{
  any_node::Nodewrap<rocoma_ros_example::RocomaRosExample> node(argc, argv, "rocoma_ros_example", 4, true);
  node.execute();
  return 0;
}
