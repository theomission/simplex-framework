#ifndef SIMPLEX_SUPPORT_DOUBLY_LINKED_LIST_H
#define SIMPLEX_SUPPORT_DOUBLY_LINKED_LIST_H

#include <Simplex/Support/PoolAllocator.h>

namespace Simplex
{
    namespace Support
    {
        class DoublyLinkedList
        {
        public:

            struct Node
            {
                Node* Next = nullptr;
                Node* Previous = nullptr;
                void* Value;
            };

            DoublyLinkedList();
            DoublyLinkedList(U32 nodesPerAllocation);
            ~DoublyLinkedList();

            void PushBack ( void* );
            void PushFront ( void* );

            void* PopBack ();
            void* PopFront ();

            Node* Last ();
            Node* First ();
            Node* At( U32 index );
            void* RemoveAt( U32 index );

        private:
            Node* CreateNode();
            void DeleteNode( Node* node );
            void CleanupNodes();
            void SetupAllocator(U32 nodeCount);
            void DeleteAllocator();

            int mNodeCountForMemoryAllocation = 1;
            int mNodeCount = 0;

            Node* mFirst = nullptr;
            Node* mLast = nullptr;

            PoolAllocator* mPoolAllocator = nullptr;
            void* mPoolMemoryAddress = nullptr;
        };
    }
}

#endif