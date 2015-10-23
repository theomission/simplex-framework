#include <Simplex/Testing.h>
#include <Simplex/Support/PoolAllocator.h>
#include "MockStruct.h"

using namespace Simplex::Support;

class SimplexSupportPoolAllocator : public ::testing::Test {
    public:
     protected:
      virtual void SetUp()
      {
        int size = 1 * 1024 * 1024; // 1MB
        void* memory = malloc(size);
        mAllocator = new PoolAllocator(sizeof(MockStructBig), alignof(MockStructBig), size, memory);
      };

      virtual void TearDown()
      {
        mAllocator->~PoolAllocator();
        free(mAllocator);
      };

      PoolAllocator* mAllocator;
};

TEST_F ( SimplexSupportPoolAllocator, InheritsFromAllocator )
{
    ASSERT_TRUE ( dynamic_cast< Simplex::Support::Allocator* >( mAllocator ) );
}

TEST_F ( SimplexSupportPoolAllocator, AllocateWillAllocateMemory )
{
    void* memory = mAllocator->Allocate(sizeof(MockStructBig), alignof(MockStructBig));
    MockStructBig* ms = new(memory) MockStructBig();

    ASSERT_EQ ( 8, sizeof(ms) );

    mAllocator->Deallocate(ms);
}

TEST_F ( SimplexSupportPoolAllocator, GetUsedMemoryReturnsMemoryUsed )
{
  void* memory = mAllocator->Allocate(sizeof(MockStructBig), alignof(MockStructBig));
  MockStructBig* ms = new(memory) MockStructBig();

  ASSERT_EQ ( mAllocator->GetUsedMemory(), 16 ); // This includes header that's why it's not 4

  mAllocator->Deallocate(ms);
}

TEST_F ( SimplexSupportPoolAllocator, GetAllocationCountReturnsCorrectly )
{
  void* memory = mAllocator->Allocate(sizeof(MockStructBig), alignof(MockStructBig));
  MockStructBig* ms = new(memory) MockStructBig();

  ASSERT_EQ ( mAllocator->GetAllocationCount(), 1 );

  mAllocator->Deallocate(ms);
}

TEST_F ( SimplexSupportPoolAllocator, DeallocateWorks )
{
  void* memory = mAllocator->Allocate(sizeof(MockStructBig), alignof(MockStructBig));
  MockStructBig* ms = new(memory) MockStructBig();

  ASSERT_EQ ( mAllocator->GetAllocationCount(), 1 );

  mAllocator->Deallocate(ms);

  ASSERT_EQ ( mAllocator->GetAllocationCount(), 0 );
}
