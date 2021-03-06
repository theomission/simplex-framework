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
        mMemory = malloc(size);
        mAllocator = new Simplex::Support::LinearAllocator(size, mMemory);
        Simplex::Support::Globals::Instance()->Allocator = mAllocator;
      };

      virtual void TearDown()
      {
        mAllocator->~LinearAllocator();
        delete(mAllocator);
        free(mMemory);
      };

      void* mMemory;
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
