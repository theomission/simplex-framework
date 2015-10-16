#include "Simplex/Testing.h"

namespace Simplex
{
  namespace Testing
  {

    void Runner::SetArguments (int argc, char **argv)
    {
      mArgc = argc;
      mArgv = argv;
    }

    void Runner::Startup ()
    {
      testing::InitGoogleTest(&mArgc, mArgv);
    }

    void Runner::Run ()
    {
      mResult = RUN_ALL_TESTS();
    }

    int Runner::GetTestResult()
    {
      return mResult;
    }

  }
}