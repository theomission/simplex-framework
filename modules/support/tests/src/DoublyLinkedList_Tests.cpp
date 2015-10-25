#include <Simplex/Testing.h>
#include <Simplex/Support/LinkedListAllocator.h>
#include <Simplex/Support/PoolAllocator.h>
#include <Simplex/Support/DoublyLinkedList.h>
#include "MockStruct.h"

using namespace Simplex::Support;

class SimplexSupportDoublyLinkedList : public ::testing::Test {
    public:
     protected:
      virtual void SetUp()
      {
        int size = 1 * 1024 * 1024; // 1MB
        void* memory = malloc(size);
        mAllocator = new Simplex::Support::LinkedListAllocator(size, memory);
        Simplex::Support::Globals::Instance()->Allocator = mAllocator;
      };

      virtual void TearDown()
      {
        mAllocator->~LinkedListAllocator();
        free(mAllocator);
      };

      Simplex::Support::LinkedListAllocator* mAllocator;
};

TEST_F( SimplexSupportDoublyLinkedList, NodeHasNextPointer )
{
    DoublyLinkedList::Node n;
    ASSERT_EQ ( n.Next, nullptr);
}

TEST_F( SimplexSupportDoublyLinkedList, NodeHasPreviousPointer )
{
    DoublyLinkedList::Node n;
    ASSERT_EQ ( n.Previous, nullptr);
}

//
//  Push Back
//

TEST_F( SimplexSupportDoublyLinkedList, PushBackAddsElement )
{
    MockStruct* m = new MockStruct();
    DoublyLinkedList list;

    list.PushBack( m );

    ASSERT_EQ ( (MockStruct*)list.Last()->Value, m );
}

TEST_F( SimplexSupportDoublyLinkedList, PushBackSetsPreviousAndNextCorrectly )
{
    MockStruct* m1 = new MockStruct();
    MockStruct* m2 = new MockStruct();

    DoublyLinkedList list;

    list.PushBack( m1 );
    list.PushBack( m2 );

    ASSERT_EQ( list.Last()->Previous->Value, m1);
    ASSERT_EQ( list.First()->Next->Value, m2);
}

TEST_F( SimplexSupportDoublyLinkedList, PushBackSetsFirstElementIfNoElementPresent )
{
    MockStruct* m = new MockStruct();
    DoublyLinkedList list;

    list.PushBack( m );

    ASSERT_EQ ( (MockStruct*)list.First()->Value, m );
}

TEST_F( SimplexSupportDoublyLinkedList, PushBackReservesMemoryToHoldOneNodeByDefault )
{
    ASSERT_EQ(mAllocator->GetAllocationCount(), 0);

    MockStruct* m = new MockStruct();
    DoublyLinkedList list;
    list.PushBack(m);

    ASSERT_EQ(mAllocator->GetAllocationCount(), 1);
}

//
//  Push Front
//

TEST_F( SimplexSupportDoublyLinkedList, PushFrontAddsElement )
{
    MockStruct* m = new MockStruct();
    DoublyLinkedList list;

    list.PushFront( m );

    ASSERT_EQ ( (MockStruct*)list.First()->Value, m );
}

TEST_F( SimplexSupportDoublyLinkedList, PushFrontSetsLastElementIfNoElementPresent )
{
    MockStruct* m = new MockStruct();
    DoublyLinkedList list;

    list.PushFront( m );

    ASSERT_EQ ( (MockStruct*)list.Last()->Value, m );
}

TEST_F( SimplexSupportDoublyLinkedList, PushFrontReservesMemoryToHoldOneNodeByDefault )
{
    ASSERT_EQ(mAllocator->GetAllocationCount(), 0);

    MockStruct* m = new MockStruct();
    DoublyLinkedList list;
    list.PushFront(m);

    ASSERT_EQ(mAllocator->GetAllocationCount(), 1);
}

TEST_F( SimplexSupportDoublyLinkedList, PushFrontPreservesConnectionToPreviousFirst )
{
    MockStruct* m1 = new MockStruct();
    MockStruct* m2 = new MockStruct();

    DoublyLinkedList list;

    list.PushFront(m1);
    list.PushFront(m2);

    ASSERT_EQ(list.First()->Next->Value, (MockStruct*)m1);
}

TEST_F( SimplexSupportDoublyLinkedList, PushFrontSetsPreviousAndNextCorrectly )
{
    MockStruct* m1 = new MockStruct();
    MockStruct* m2 = new MockStruct();

    DoublyLinkedList list;

    list.PushFront( m1 );
    list.PushFront( m2 );

    ASSERT_EQ( list.Last()->Previous->Value, m2);
    ASSERT_EQ( list.First()->Next->Value, m1);
}


//
//  Pop Back
//

TEST_F( SimplexSupportDoublyLinkedList, PopBackDeallocatesNode )
{
    MockStruct* m1 = new MockStruct();

    DoublyLinkedList list;

    list.PushBack(m1);

    ASSERT_EQ(mAllocator->GetAllocationCount(), 1);

    list.PopBack();

    ASSERT_EQ(mAllocator->GetAllocationCount(), 0);
    ASSERT_EQ(mAllocator->GetUsedMemory(), 0);
}

TEST_F( SimplexSupportDoublyLinkedList, PopBackUpdatesFirstWhenListIsEmptied )
{
    MockStruct* m = new MockStruct();
    DoublyLinkedList list;

    list.PushBack( m );
    list.PopBack();

    ASSERT_EQ ( list.First(), nullptr );
}

TEST_F( SimplexSupportDoublyLinkedList, PopBackReturnsObject )
{
    MockStruct* m1 = new MockStruct();

    DoublyLinkedList list;

    list.PushBack(m1);
    MockStruct*m2 = (MockStruct*) list.PopBack();

    ASSERT_EQ(m2, m1);
}

//
//  Pop Front
//

TEST_F( SimplexSupportDoublyLinkedList, PopFrontDeallocatesNode )
{
    MockStruct* m1 = new MockStruct();

    DoublyLinkedList list;

    list.PushFront(m1);

    ASSERT_EQ(mAllocator->GetAllocationCount(), 1);

    list.PopFront();

    ASSERT_EQ(mAllocator->GetAllocationCount(), 0);
    ASSERT_EQ(mAllocator->GetUsedMemory(), 0);
}

TEST_F( SimplexSupportDoublyLinkedList, PopFrontUpdatesLastWhenListIsEmptied )
{
    MockStruct* m = new MockStruct();
    DoublyLinkedList list;

    list.PushFront( m );
    list.PopFront();

    ASSERT_EQ ( list.Last(), nullptr );
}

TEST_F( SimplexSupportDoublyLinkedList, PopFrontReturnsObject )
{
    MockStruct* m1 = new MockStruct();

    DoublyLinkedList list;

    list.PushFront(m1);
    MockStruct*m2 = (MockStruct*) list.PopFront();

    ASSERT_EQ(m2, m1);
}

//
//  Last
//
TEST_F( SimplexSupportDoublyLinkedList, LastPreservesConnectionToPreviousLast )
{
    MockStruct* m1 = new MockStruct();
    MockStruct* m2 = new MockStruct();

    DoublyLinkedList list;

    list.PushBack(m1);
    list.PushBack(m2);

    ASSERT_EQ(list.Last()->Previous->Value, (MockStruct*)m1);
}

TEST_F( SimplexSupportDoublyLinkedList, LastReturnsLastAddedElement )
{
    MockStruct* m1 = new MockStruct();
    MockStruct* m2 = new MockStruct();
    MockStruct* m3 = new MockStruct();

    DoublyLinkedList list;

    list.PushBack(m1);

    ASSERT_EQ(list.Last()->Value, (MockStruct*)m1);

    list.PushBack(m2);

    ASSERT_EQ(list.Last()->Value, (MockStruct*)m2);

    list.PushBack(m3);

    ASSERT_EQ(list.Last()->Value, (MockStruct*)m3);

}

//
//  First
//
TEST_F( SimplexSupportDoublyLinkedList, FirstReturnsLastElementPushedToFront )
{
    MockStruct* m1 = new MockStruct();
    MockStruct* m2 = new MockStruct();
    MockStruct* m3 = new MockStruct();

    DoublyLinkedList list;

    list.PushFront(m1);

    ASSERT_EQ(list.First()->Value, (MockStruct*)m1);

    list.PushFront(m2);

    ASSERT_EQ(list.First()->Value, (MockStruct*)m2);

    list.PushFront(m3);

    ASSERT_EQ(list.First()->Value, (MockStruct*)m3);
}

//
//  At
//
TEST_F( SimplexSupportDoublyLinkedList, AtReturnsObjectAtSpecifiedIndex )
{
    MockStruct* m1 = new MockStruct();
    MockStruct* m2 = new MockStruct();
    MockStruct* m3 = new MockStruct();

    DoublyLinkedList list;

    list.PushBack(m1);
    list.PushBack(m2);
    list.PushBack(m3);

    ASSERT_EQ(list.At(0)->Value, (MockStruct*)m1);
    ASSERT_EQ(list.At(1)->Value, (MockStruct*)m2);
    ASSERT_EQ(list.At(2)->Value, (MockStruct*)m3);
}

//
//  RemoveAt
//
TEST_F( SimplexSupportDoublyLinkedList, RemoveAtLeavesAConsistentList )
{
    MockStruct* m1 = new MockStruct();
    MockStruct* m2 = new MockStruct();
    MockStruct* m3 = new MockStruct();

    DoublyLinkedList list;

    list.PushBack(m1);
    list.PushBack(m2);
    list.PushBack(m3);

    list.RemoveAt(1);

    ASSERT_EQ((MockStruct*)list.First()->Next->Value, m3);
    ASSERT_EQ((MockStruct*)list.Last()->Previous->Value, m1);
}

TEST_F( SimplexSupportDoublyLinkedList, RemoveAtReturnsValue )
{
    MockStruct* m1 = new MockStruct();
    MockStruct* m2 = new MockStruct();

    DoublyLinkedList list;

    list.PushBack(m1);
    list.PushBack(m2);

    MockStruct* result = (MockStruct*) list.RemoveAt(1);

    ASSERT_EQ(result, m2);
}

//
//  With Pool Allocator
//
TEST_F( SimplexSupportDoublyLinkedList, CustomConstructorAllocatesMemoryToHoldNNodes )
{
    DoublyLinkedList list(5);
    ASSERT_GT( mAllocator->GetUsedMemory(), sizeof(PoolAllocator) + 5 * sizeof(DoublyLinkedList::Node) );
}

TEST_F( SimplexSupportDoublyLinkedList, CustomConstructorUsesAllocatorMemoryWhenCreatingNodes )
{
    DoublyLinkedList list(5);

    SIZE before = mAllocator->GetUsedMemory();

    MockStruct* m1 = new MockStruct();
    MockStruct* m2 = new MockStruct();
    MockStruct* m3 = new MockStruct();

    list.PushFront(m1);
    list.PushFront(m2);
    list.PushFront(m3);

    SIZE after = mAllocator->GetUsedMemory();

    ASSERT_EQ(before, after);
}

//
//  Destructor
//
TEST_F( SimplexSupportDoublyLinkedList, DestructorDeallocatesNodes )
{
    MockStruct* m1 = new MockStruct();
    MockStruct* m2 = new MockStruct();
    MockStruct* m3 = new MockStruct();

    DoublyLinkedList list;

    list.PushBack(m1);
    list.PushBack(m2);
    list.PushBack(m3);

    list.~DoublyLinkedList();

    ASSERT_EQ(mAllocator->GetAllocationCount(), 0);
}
