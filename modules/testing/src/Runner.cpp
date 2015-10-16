#include "Simplex/Testing.h"

namespace Simplex
{
  namespace Testing
  {
    Runner::Runner (int argc, char **argv)
    {
      testing::InitGoogleTest(&argc, argv);
    }

    int Runner::Start ()
    {
      return RUN_ALL_TESTS();
    }
  }
}