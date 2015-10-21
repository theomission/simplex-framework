#ifndef __CI_BUILD__
#include <Simplex/Testing.h>
#include <Simplex/Application.h>

using namespace Simplex;
TEST ( SimplexApplication, StartupConfiguresMemory )
{
  Application a;

  a.AllocateMemory(100);
  a.Startup();

  Support::Globals* globals = Simplex::Support::Globals::Instance();

  EXPECT_GT( globals->Allocator->GetSize(), 99);
  a.Shutdown();
}

TEST ( SimplexApplication, StartupInitializesGraphics )
{
  Application a;

  a.AllocateMemory(100);
  a.Startup();

  EXPECT_EQ( Graphics::Subsystem::Instance()->Initialized, true );
  a.Shutdown();
}

TEST ( SimplexApplication, StartupInitializesEditor )
{
  Application a;

  a.AllocateMemory(100);
  a.Startup();

  EXPECT_EQ( Editor::Subsystem::Instance()->Initialized, true );
  a.Shutdown();
}
#endif
