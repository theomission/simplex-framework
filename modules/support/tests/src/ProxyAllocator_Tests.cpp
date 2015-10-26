#include <Simplex/Testing.h>
#include <Simplex/Support/ProxyAllocator.h>
#include <Simplex/Support/LinkedListAllocator.h>
#include "MockStruct.h"
#include<Simplex/Support/Assert.h>

using namespace Simplex::Support;

class SimplexSupportProxyAllocator : public ::testing::Test {
    public:
     protected:
      virtual void SetUp()
      {
        int size = 1 * 1024 * 1024; // 1MB
        mMemory = malloc(size);
        mLinkedListAllocator = new LinkedListAllocator(size, mMemory);
        mAllocator = new ProxyAllocator(*mLinkedListAllocator);
      };

      virtual void TearDown()
      {
        mAllocator->~ProxyAllocator();
        delete(mAllocator);
        mLinkedListAllocator->~LinkedListAllocator();
        delete(mLinkedListAllocator);
        free(mMemory);
      };

      void* mMemory;
      ProxyAllocator* mAllocator;
      LinkedListAllocator* mLinkedListAllocator;
};

TEST_F ( SimplexSupportProxyAllocator, InheritsFromAllocator )
{
    ASSERT_TRUE ( dynamic_cast< Simplex::Support::Allocator* >( mAllocator ) );
}

TEST_F ( SimplexSupportProxyAllocator, AllocateWillAllocateMemory )
{
    void* memory = mAllocator->Allocate(sizeof(MockStruct), alignof(MockStruct));
    MockStruct* ms = new(memory) MockStruct();

    ASSERT_EQ ( 8, sizeof(ms) );

    mAllocator->Deallocate(ms);
}

TEST_F ( SimplexSupportProxyAllocator, GetUsedMemoryReturnsMemoryUsed )
{
  void* memory = mAllocator->Allocate(sizeof(MockStruct), alignof(MockStruct));
  MockStruct* ms = new(memory) MockStruct();

  ASSERT_EQ ( mAllocator->GetUsedMemory(), 20 ); // This includes header that's why it's not 4

  mAllocator->Deallocate(ms);
}

TEST_F ( SimplexSupportProxyAllocator, GetAllocationCountReturnsCorrectly )
{
  void* memory = mAllocator->Allocate(sizeof(MockStruct), alignof(MockStruct));
  MockStruct* ms = new(memory) MockStruct();

  ASSERT_EQ ( mAllocator->GetAllocationCount(), 1 );

  mAllocator->Deallocate(ms);
}

TEST_F ( SimplexSupportProxyAllocator, DeallocateWorks )
{
  void* memory = mAllocator->Allocate(sizeof(MockStruct), alignof(MockStruct));
  MockStruct* ms = new(memory) MockStruct();

  ASSERT_EQ ( mAllocator->GetAllocationCount(), 1 );

  mAllocator->Deallocate(ms);

  ASSERT_EQ ( mAllocator->GetAllocationCount(), 0 );
}
