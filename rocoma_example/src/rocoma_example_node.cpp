// rocoma example
#include "rocoma_example/RocomaExample.hpp"

// nodewrap
#include "any_node/Nodewrap.hpp"


int main(int argc, char **argv)
{
  any_node::Nodewrap<rocoma_example::RocomaExample> node(argc, argv, "rocoma_example", 4, true, 1);
  node.execute();
  return 0;
}
