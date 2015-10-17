#include <Simplex/Testing.h>
#include <Simplex/Support/Subsystem.h>
#include <Simplex/Graphics/Subsystem.h>

using namespace Simplex::Graphics;

TEST ( SimplexGraphicsSubsystem, IsASingleton )
{
    Simplex::Support::Globals::Instance()->Allocator = new Support::StackAllocator(100);
    EXPECT_TRUE ( Subsystem::Instance() != NULL );
}

TEST ( SimplexGraphicsSubsystem, InheritsFromSimplexSupportSubsystem )
{
    ASSERT_TRUE ( dynamic_cast< Simplex::Support::Subsystem* >( Subsystem::Instance() ) );
}

TEST ( SimplexGraphicsSubsystem, StartupUpdateInitialize )
{
    Subsystem::Instance()->Startup();
    ASSERT_TRUE ( Subsystem::Instance()->Initialized );
}

TEST ( SimplexGraphicsSubsystem, ShutdownUpdatesInitialize )
{
    Subsystem::Instance()->Shutdown();
    ASSERT_FALSE ( Subsystem::Instance()->Initialized );
}
