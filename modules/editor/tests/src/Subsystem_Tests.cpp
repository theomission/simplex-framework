#include <Simplex/Testing.h>
#include <Simplex/Support/LinearAllocator.h>
#include <Simplex/Support/Subsystem.h>
#include <Simplex/Editor/Subsystem.h>

using namespace Simplex::Editor;

class SimplexEditorSubsystem : public ::testing::Test {
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

TEST_F ( SimplexEditorSubsystem, IsASingleton )
{
    EXPECT_TRUE ( Subsystem::Instance() != NULL );
    ((Simplex::Support::LinearAllocator*)Support::Globals::Instance()->Allocator)->Clear();
}

TEST_F ( SimplexEditorSubsystem, InheritsFromSimplexSupportSubsystem )
{
    ASSERT_TRUE ( dynamic_cast< Support::Subsystem* >( Subsystem::Instance() ) );
    ((Simplex::Support::LinearAllocator*)Support::Globals::Instance()->Allocator)->Clear();
}

// TODO see how to fix these
// TEST ( SimplexEditorSubsystem, StartupUpdatesInitialize )
// {
//     Subsystem::Instance()->Startup();
//     ASSERT_TRUE ( Subsystem::Instance()->Initialized );
// }

// TEST ( SimplexEditorSubsystem, ShutdownUpdatesInitialize )
// {
//     Subsystem::Instance()->Shutdown();
//     ASSERT_FALSE ( Subsystem::Instance()->Initialized );
// }
