#ifndef SIMPLEX_TEST_RUNNER_H
#define SIMPLEX_TEST_RUNNER_H

#include "gtest/gtest.h"

namespace Simplex
{
  namespace Testing
  {
    class Runner
    {
    public:
      Runner (int, char **);
      int Start ();
    };
  }
}

#endif