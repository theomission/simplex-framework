#ifndef SIMPLEX_TEST_RUNNER_H
#define SIMPLEX_TEST_RUNNER_H

#include "gtest/gtest.h"
#include "Simplex/Application.h"

namespace Simplex
{
  namespace Testing
  {
    class Runner : public Simplex::Application
    {
        public:
            void SetArguments(int argc, char **argv);
            virtual void Startup() override;
            virtual void Run() override;
            int GetTestResult();
        private:
            int mArgc;
            char** mArgv;
            int mResult;
    };
  }
}

#endif