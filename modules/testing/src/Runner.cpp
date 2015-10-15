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

int main ( int argc, char **argv )
{
  Simplex::Testing::Runner testRunner = Simplex::Testing::Runner ( argc, argv );
  return testRunner.Start ();
}
