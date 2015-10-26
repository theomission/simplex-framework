#include <Simplex/Testing.h>
#include <Simplex/Application.h>
#include <Simplex/Support/Subsystem.h>
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

class ApplicationMock : public Simplex::Application
{
  virtual void FrameStep() override
  {
    Support::Globals::Instance()->ShouldShutdown = true;
  };
};
TEST ( SimplexApplication, AllocateMemoryReservesMemory )
{
  ApplicationMock a;

  a.AllocateMemory(100);

  Support::Globals* globals = Simplex::Support::Globals::Instance();

  EXPECT_GT( globals->Allocator->GetSize(), 99);
  a.Shutdown();
}

TEST ( SimplexApplication, SetSubsystemCountReservesMemory )
{
  ApplicationMock a;

  a.AllocateMemory(1024);

  a.SetSubsystemCount(2);

  Support::Globals* globals = Simplex::Support::Globals::Instance();

  EXPECT_GT( globals->Allocator->GetUsedMemory(), 100 );
  a.Shutdown();
}

TEST ( SimplexApplication, AddSubsystemAddsSubsystemAndStartupStartsThem )
{
  ApplicationMock a;
  SubsystemMock s;

  a.AllocateMemory(1024);
  a.SetSubsystemCount(1);
  a.AddSubsystem(&s);
  a.Startup();

  ASSERT_EQ( s.FunctionCalled, "Startup" );
}

TEST ( SimplexApplication, UpdateUpdatesSubsystems )
{
  ApplicationMock a;
  SubsystemMock s;

  a.AllocateMemory(1024);
  a.SetSubsystemCount(1);
  a.AddSubsystem(&s);
  a.Startup();
  a.Run();

  ASSERT_EQ( s.FunctionCalled, "Update" );
}

TEST ( SimplexApplication, ShutdownShutdownsSubsystems )
{
  ApplicationMock a;
  SubsystemMock s;

  a.AllocateMemory(1024);
  a.SetSubsystemCount(1);
  a.AddSubsystem(&s);
  a.Startup();
  a.Shutdown();

  ASSERT_EQ( s.FunctionCalled, "Shutdown" );
}