#include <Simplex/Testing.h>
#include <Simplex/Support/LinkedListAllocator.h>
#include <Simplex/Support/Subsystem.h>
#include <Simplex/Graphics/Subsystem.h>

using namespace Simplex::Graphics;

class SimplexGraphicsSubsystem : public ::testing::Test {
    public:
     protected:
      virtual void SetUp()
      {
        int size = 1 * 1024 * 1024; // 1MB
        mMemory = malloc(size);
        mAllocator = new Simplex::Support::LinkedListAllocator(size, mMemory);
        Simplex::Support::Globals::Instance()->Allocator = mAllocator;
      };

      virtual void TearDown()
      {
        Subsystem::Destroy();
        mAllocator->~LinkedListAllocator();
        delete(mAllocator);
        free(mMemory);
      };

      void* mMemory;
      Simplex::Support::LinkedListAllocator* mAllocator;
};

TEST_F ( SimplexGraphicsSubsystem, IsASingleton )
{
    EXPECT_TRUE ( Subsystem::Instance() != NULL );
}

TEST_F ( SimplexGraphicsSubsystem, InheritsFromSimplexSupportSubsystem )
{
    Subsystem* s = Subsystem::Instance();
    ASSERT_TRUE ( dynamic_cast< Simplex::Support::Subsystem* >( s ) );
}

#ifndef __CI_BUILD__
TEST_F ( SimplexGraphicsSubsystem, StartupUpdatesInitialized )
{
    Subsystem::Instance()->Startup();
    ASSERT_TRUE ( Subsystem::Instance()->Initialized );
    Subsystem::Instance()->Shutdown();
}

TEST_F ( SimplexGraphicsSubsystem, ShutdownUpdatesInitialized )
{
    Subsystem::Instance()->Startup();
    Subsystem::Instance()->Shutdown();
    ASSERT_FALSE ( Subsystem::Instance()->Initialized );
}
#endif