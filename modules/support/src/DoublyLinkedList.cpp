#include <Simplex/Support/DoublyLinkedList.h>
#include <Simplex/Support/Globals.h>
#include <stdio.h>

namespace Simplex
{
    namespace Support
    {
        DoublyLinkedList::DoublyLinkedList()
        {}

        DoublyLinkedList::DoublyLinkedList(U32 nodeCount)
        {
            SetupAllocator(nodeCount);
        }


        DoublyLinkedList::~DoublyLinkedList()
        {
            CleanupNodes();

            if(mPoolAllocator != nullptr)
                DeleteAllocator();
        }

        void DoublyLinkedList::PushBack( void * value)
        {
            Node* node = CreateNode();

            node->Value = value;
            node->Next = nullptr;
            node->Previous = mLast;

            if(mLast != nullptr)
                mLast->Next = node;

            mLast = node;

            if(mFirst == nullptr)
                mFirst = mLast;
        }

        void DoublyLinkedList::PushFront ( void * value )
        {
            Node* node = CreateNode();

            node->Value = value;
            node->Next = mFirst;
            node->Previous = nullptr;

            if(mFirst != nullptr)
                mFirst->Previous = node;

            mFirst = node;

            if(mLast == nullptr)
                mLast = mFirst;
        }

        DoublyLinkedList::Node* DoublyLinkedList::CreateNode()
        {
            void* memory;

            if(mPoolAllocator != nullptr)
                memory = mPoolAllocator->Allocate(sizeof(Node), alignof(Node));
            else
                memory = Globals::Instance()->Allocator->Allocate(sizeof(Node), alignof(Node));

            return new(memory) Node();
        }

        void* DoublyLinkedList::PopBack ()
        {
            void* result = mLast->Value;
            Node* newLast = mLast->Previous;

            DeleteNode(mLast);

            mLast = newLast;

            if(newLast == nullptr)
                mFirst = nullptr;

            return result;
        }

        void* DoublyLinkedList::PopFront ()
        {
            void* result = mFirst->Value;
            Node* newFirst = mFirst->Next;

            DeleteNode(mFirst);

            mFirst = newFirst;

            if(newFirst == nullptr)
                mLast = nullptr;

            return result;
        }

        void DoublyLinkedList::DeleteNode(Node* node)
        {

            if(mFirst == node)
                mFirst = node->Next;

            if(mLast == node)
                mLast = node->Previous;

            if(node->Previous)
                node->Previous->Next = node->Next;

            if(node->Next)
                node->Next->Previous = node->Previous;

            node->~Node();

            if(mPoolAllocator != nullptr)
                mPoolAllocator->Deallocate(node);
            else
                Globals::Instance()->Allocator->Deallocate(node);
        }

        DoublyLinkedList::Node* DoublyLinkedList::Last()
        {
            return mLast;
        }

        DoublyLinkedList::Node* DoublyLinkedList::First()
        {
            return mFirst;
        }

        DoublyLinkedList::Node* DoublyLinkedList::At( U32 index )
        {
            Node* currentNode = mFirst;

            while(index > 0)
            {
                currentNode = currentNode->Next;
                index--;
            }

            return currentNode;
        }

        void* DoublyLinkedList::RemoveAt( U32 index )
        {
            Node* node = At(index);

            void* result = node->Value;

            DeleteNode(node);

            return result;
        }

        void DoublyLinkedList::CleanupNodes()
        {
            while(mLast != nullptr)
            {
                PopBack();
            }
        }

        void DoublyLinkedList::SetupAllocator(U32 nodeCount)
        {
            void* poolAllocatorMemory = Globals::Instance()->Allocator->Allocate(sizeof(PoolAllocator), alignof(PoolAllocator));
            SIZE size = sizeof(Node) * nodeCount + alignof(Node) * nodeCount;

            mPoolMemoryAddress = Globals::Instance()->Allocator->Allocate(size, alignof(PoolAllocator));
            mPoolAllocator = new(poolAllocatorMemory) PoolAllocator(sizeof(Node), alignof(Node), size, mPoolMemoryAddress);
        }

        void DoublyLinkedList::DeleteAllocator()
        {

            mPoolAllocator->~PoolAllocator();

            Globals::Instance()->Allocator->Deallocate(mPoolMemoryAddress);
            Globals::Instance()->Allocator->Deallocate(mPoolAllocator);
        }

    }
}