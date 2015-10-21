#include <Simplex/Testing.h>
#include <Simplex/Support/StackAllocator.h>
#include "MockStruct.h"

using namespace Simplex::Support;

class SimplexSupportStackAllocator : public ::testing::Test {
    public:
     protected:
      virtual void SetUp()
      {
        int size = 1 * 1024 * 1024; // 1MB
        void* memory = malloc(size);
        mAllocator = new StackAllocator(size, memory);
      };

      virtual void TearDown()
      {
        mAllocator->~StackAllocator();
        free(mAllocator);
      };

      StackAllocator* mAllocator;
};

TEST_F ( SimplexSupportStackAllocator, InheritsFromAllocator )
{
    ASSERT_TRUE ( dynamic_cast< Simplex::Support::Allocator* >( mAllocator ) );
}

TEST_F ( SimplexSupportStackAllocator, AllocateWillAllocateMemory )
{
    void* memory = mAllocator->Allocate(sizeof(MockStruct), alignof(MockStruct));
    MockStruct* ms = new(memory) MockStruct();

    ASSERT_EQ ( 8, sizeof(ms) );

    mAllocator->Deallocate(ms);
}

TEST_F ( SimplexSupportStackAllocator, GetUsedMemoryReturnsMemoryUsed )
{
  void* memory = mAllocator->Allocate(sizeof(MockStruct), alignof(MockStruct));
  MockStruct* ms = new(memory) MockStruct();

  ASSERT_EQ ( mAllocator->GetUsedMemory(), 8 ); // This includes header that's why it's not 4

  mAllocator->Deallocate(ms);
}

TEST_F ( SimplexSupportStackAllocator, GetAllocationCountReturnsCorrectly )
{
  void* memory = mAllocator->Allocate(sizeof(MockStruct), alignof(MockStruct));
  MockStruct* ms = new(memory) MockStruct();

  ASSERT_EQ ( mAllocator->GetAllocationCount(), 1 );

  mAllocator->Deallocate(ms);
}
