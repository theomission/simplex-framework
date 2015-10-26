#include <Simplex/Testing.h>
#include <Simplex/Application.h>
#include <Simplex/Support/Subsystem.h>
using namespace Simplex;

class SubsystemMock : public Simplex::Support::Subsystem
{
  public:
    std::string FunctionCalled;

    virtual void Startup() override
    {
      FunctionCalled = "Startup";
      Initialized = true;
    };
    virtual void Update() override
    {
      FunctionCalled = "Update";
    };
    virtual void Shutdown() override
    {
      FunctionCalled = "Shutdown";
    };
};

TEST ( SimplexApplication, StartupConfiguresMemory )
{
  Application a;

  a.AllocateMemory(100);
  a.Startup();

  Support::Globals* globals = Simplex::Support::Globals::Instance();

  EXPECT_GT( globals->Allocator->GetSize(), 99);
  a.Shutdown();
}

TEST ( SimplexApplication, SetSubsystemCountReservesMemory )
{
  Application a;

  a.AllocateMemory(1024);

  a.SetSubsystemCount(2);
  a.Startup();

  Support::Globals* globals = Simplex::Support::Globals::Instance();

  EXPECT_GT( globals->Allocator->GetUsedMemory(), 0 );
  a.Shutdown();
}
// TEST ( SimplexApplication, AddSubsystemAddsSubsystem )
// {
//   Application a;
//   SubsystemMock s;

//   a.AddSubsystem(&s);

//   a.Startup();

//   ASSERT_TRUE( s.FunctionCalled == "Startup" );
// }