#include <Simplex/Testing.h>
#include <Simplex/Support/Subsystem.h>
#include <Simplex/Editor/Subsystem.h>

using namespace Simplex::Editor;

TEST ( SimplexEditorSubsystem, IsASingleton )
{
    Simplex::Support::Globals::Instance()->Allocator = new Support::StackAllocator(100);
    EXPECT_TRUE ( Subsystem::Instance() != NULL );
}

TEST ( SimplexEditorSubsystem, InheritsFromSimplexSupportSubsystem )
{
    ASSERT_TRUE ( dynamic_cast< Support::Subsystem* >( Subsystem::Instance() ) );
}

TEST ( SimplexEditorSubsystem, StartupUpdatesInitialize )
{
    Subsystem::Instance()->Startup();
    ASSERT_TRUE ( Subsystem::Instance()->Initialized );
}

TEST ( SimplexEditorSubsystem, ShutdownUpdatesInitialize )
{
    Subsystem::Instance()->Shutdown();
    ASSERT_FALSE ( Subsystem::Instance()->Initialized );
}
