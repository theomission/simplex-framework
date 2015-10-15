#include <Simplex/Testing.h>
#include <Simplex/Support/StackAllocator.h>

struct MockStruct
{
    U32 aValue;
};

TEST ( SimplexSupportStackAllocator, InheritsFromAllocator )
{
    Simplex::Support::StackAllocator s(1);
    ASSERT_TRUE ( dynamic_cast< Simplex::Support::Allocator* >( &s ) );
}

TEST ( SimplexSupportStackAllocator, TotalReservedReturnsCorrectly )
{
    Simplex::Support::StackAllocator s(10);

    ASSERT_EQ ( 10, s.TotalReserved() );
}

TEST ( SimplexSupportStackAllocator, AllocateWillAllocateMemory )
{
    Simplex::Support::StackAllocator s(20);
    void* memory = s.Allocate(sizeof(MockStruct), alignof(MockStruct));
    MockStruct* ms = new(memory) MockStruct();
    ASSERT_EQ ( 8, sizeof(ms) );
}

TEST ( SimplexSupportStackAllocator, TotalAllocatedReturnsCorrectly )
{
    Simplex::Support::StackAllocator s(20);
    void* memory = s.Allocate(sizeof(MockStruct), alignof(MockStruct));
    ASSERT_EQ ( 8, s.TotalAllocated() );
}

TEST ( SimplexSupportStackAllocator, TotalAvailableReturnsCorrectly )
{
    Simplex::Support::StackAllocator s(20);
    void* memory = s.Allocate(sizeof(MockStruct), alignof(MockStruct));
    ASSERT_EQ ( 12, s.TotalAvailable() );
}

TEST ( SimplexSupportStackAllocator, DeallocateRemovesFromStack )
{
    Simplex::Support::StackAllocator s(20);
    void* memory = s.Allocate(sizeof(MockStruct), alignof(MockStruct));
    ASSERT_EQ ( 8, s.TotalAllocated() );
    s.Deallocate(memory);
    ASSERT_EQ ( 0, s.TotalAllocated() );
}


