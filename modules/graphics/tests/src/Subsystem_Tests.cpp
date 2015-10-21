#include <Simplex/Testing.h>
#include <Simplex/Support/LinearAllocator.h>
#include <Simplex/Support/Subsystem.h>
#include <Simplex/Graphics/Subsystem.h>

using namespace Simplex::Graphics;

class SimplexGraphicsSubsystem : public ::testing::Test {
    public:
     protected:
      virtual void SetUp()
      {
        int size = 1 * 1024 * 1024; // 1MB
        void* memory = malloc(size);
        mAllocator = new Simplex::Support::LinearAllocator(size, memory);
        Simplex::Support::Globals::Instance()->Allocator = mAllocator;
      };

      virtual void TearDown()
      {
        mAllocator->~LinearAllocator();
        free(mAllocator);
      };

      Simplex::Support::LinearAllocator* mAllocator;
};

TEST_F ( SimplexGraphicsSubsystem, IsASingleton )
{
    EXPECT_TRUE ( Subsystem::Instance() != NULL );
    ((Simplex::Support::LinearAllocator*)Support::Globals::Instance()->Allocator)->Clear();
}

TEST_F ( SimplexGraphicsSubsystem, InheritsFromSimplexSupportSubsystem )
{
    ASSERT_TRUE ( dynamic_cast< Simplex::Support::Subsystem* >( Subsystem::Instance() ) );
}

TEST_F ( SimplexGraphicsSubsystem, StartupUpdateInitialize )
{
    Subsystem::Instance()->Startup();
    ASSERT_TRUE ( Subsystem::Instance()->Initialized );
    ((Simplex::Support::LinearAllocator*)Support::Globals::Instance()->Allocator)->Clear();
}
TEST_F ( SimplexGraphicsSubsystem, ShutdownUpdatesInitialize )
{
    Subsystem::Instance()->Shutdown();
    ASSERT_FALSE ( Subsystem::Instance()->Initialized );
    ((Simplex::Support::LinearAllocator*)Support::Globals::Instance()->Allocator)->Clear();
}
