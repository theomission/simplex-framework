#include <Simplex/Testing.h>
#include <Simplex/Support/Subsystem.h>

using namespace Simplex::Support;

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

TEST ( SimplexSupportSubsystem, HasStartupMethod )
{
  SubsystemMock ss;

  ss.Startup();

  ASSERT_EQ ( ss.FunctionCalled, "Startup" );
  ASSERT_EQ ( ss.Initialized, true );

}

TEST ( SimplexSupportSubsystem, HasUpdateMethod )
{
  SubsystemMock ss;

  ss.Update();

  ASSERT_EQ ( ss.FunctionCalled, "Update" );
}

TEST ( SimplexSupportSubsystem, HasShutdownMethod )
{
  SubsystemMock ss;

  ss.Shutdown();

  ASSERT_EQ ( ss.FunctionCalled, "Shutdown" );
}
