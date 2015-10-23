#include <Simplex/Testing.h>
#include <Simplex/Support/LinkedListAllocator.h>
#include "MockStruct.h"

using namespace Simplex::Support;

class SimplexSupportLinkedListAllocator : public ::testing::Test {
    public:
     protected:
      virtual void SetUp()
      {
        int size = 1 * 1024 * 1024; // 1MB
        void* memory = malloc(size);
        mAllocator = new LinkedListAllocator(size, memory);
      };

      virtual void TearDown()
      {
        mAllocator->~LinkedListAllocator();
        free(mAllocator);
      };

      LinkedListAllocator* mAllocator;
};

TEST_F ( SimplexSupportLinkedListAllocator, InheritsFromAllocator )
{
    ASSERT_TRUE ( dynamic_cast< Simplex::Support::Allocator* >( mAllocator ) );
}

TEST_F ( SimplexSupportLinkedListAllocator, AllocateWillAllocateMemory )
{
    void* memory = mAllocator->Allocate(sizeof(MockStruct), alignof(MockStruct));
    MockStruct* ms = new(memory) MockStruct();

    ASSERT_EQ ( 8, sizeof(ms) );

    mAllocator->Deallocate(ms);
}

TEST_F ( SimplexSupportLinkedListAllocator, GetUsedMemoryReturnsMemoryUsed )
{
  void* memory = mAllocator->Allocate(sizeof(MockStruct), alignof(MockStruct));
  MockStruct* ms = new(memory) MockStruct();

  ASSERT_EQ ( mAllocator->GetUsedMemory(), 20 ); // This includes header that's why it's not 4

  mAllocator->Deallocate(ms);
}

TEST_F ( SimplexSupportLinkedListAllocator, GetAllocationCountReturnsCorrectly )
{
  void* memory = mAllocator->Allocate(sizeof(MockStruct), alignof(MockStruct));
  MockStruct* ms = new(memory) MockStruct();

  ASSERT_EQ ( mAllocator->GetAllocationCount(), 1 );

  mAllocator->Deallocate(ms);
}

TEST_F ( SimplexSupportLinkedListAllocator, DeallocateWorks )
{
  void* memory = mAllocator->Allocate(sizeof(MockStruct), alignof(MockStruct));
  MockStruct* ms = new(memory) MockStruct();

  ASSERT_EQ ( mAllocator->GetAllocationCount(), 1 );

  mAllocator->Deallocate(ms);

  ASSERT_EQ ( mAllocator->GetAllocationCount(), 0 );
}
