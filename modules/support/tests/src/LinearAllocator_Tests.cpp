#include <Simplex/Testing.h>
#include <Simplex/Support/LinearAllocator.h>

using namespace Simplex::Support;

class SimplexSupportLinearAllocator : public ::testing::Test {
    public:
        struct MockStruct
        {
            U32 aValue;
        };

     protected:

      virtual void SetUp()
      {
        int size = 1 * 1024 * 1024; // 1MB
        mAllocator = new LinearAllocator(size, malloc(size));
      };

      virtual void TearDown()
      {
        mAllocator->~LinearAllocator();
        free(mAllocator);
      };

      LinearAllocator* mAllocator;
};



TEST_F ( SimplexSupportLinearAllocator, InheritsFromAllocator )
{
    ASSERT_TRUE ( dynamic_cast< Simplex::Support::Allocator* >( mAllocator ) );
}

TEST_F ( SimplexSupportLinearAllocator, AllocateWillAllocateMemory )
{
    void* memory = mAllocator->Allocate(sizeof(MockStruct), alignof(MockStruct));
    MockStruct* ms = new(memory) MockStruct();
    ASSERT_EQ ( 8, sizeof(ms) );
    mAllocator->Clear();
}

TEST_F ( SimplexSupportLinearAllocator, ClearWillRemoveAllAllocations )
{
    void* memory = mAllocator->Allocate(sizeof(MockStruct), alignof(MockStruct));
    MockStruct* ms = new(memory) MockStruct();
    mAllocator->Clear();
    ASSERT_EQ(0, mAllocator->GetAllocationCount());
}