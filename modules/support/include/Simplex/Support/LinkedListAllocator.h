#ifndef SIMPLEX_SUPPORT_LINKED_LIST_ALLOCATOR_H
#define SIMPLEX_SUPPORT_LINKED_LIST_ALLOCATOR_H

#include <Simplex/Support/Allocator.h>

namespace Simplex
{
    namespace Support
    {
        class LinkedListAllocator : public Allocator
        {
        public:
            LinkedListAllocator(SIZE size, void* start);
            ~LinkedListAllocator();

            void* Allocate(SIZE size, U8 alignment) override;

            void Deallocate(void* p) override;

        private:

            struct AllocationHeader
            {
                SIZE Size;
                U8     Adjustment;
            };

            struct FreeBlock
            {
                SIZE     Size;
                FreeBlock* Next;
            };

            LinkedListAllocator(const LinkedListAllocator&); //Prevent copies because it might cause errors
            LinkedListAllocator& operator=(const LinkedListAllocator&);

            FreeBlock* mFreeBlocks;
        };
    }
}

#endif