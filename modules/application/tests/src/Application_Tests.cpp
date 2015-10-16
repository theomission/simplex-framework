#include <Simplex/Testing.h>
#include <Simplex/Application.h>

using namespace Simplex;

TEST ( SimplexApplication, StartupConfiguresMemory )
{
  Application a;

  a.AllocateMemory(100);
  a.Startup();

  Globals* globals = Simplex::Support::Globals::Instance();

  EXPECT_GT( globals->allocator->TotalReserved(), 10);
}