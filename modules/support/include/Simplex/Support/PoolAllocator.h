#ifndef SIMPLEX_SUPPORT_POOL_ALLOCATOR_H
#define SIMPLEX_SUPPORT_POOL_ALLOCATOR_H

#include <Simplex/Support/Allocator.h>

namespace Simplex
{
    namespace Support
    {
        class PoolAllocator : public Allocator
        {
        public:
            PoolAllocator(SIZE objectSize, U8 objectAlign, SIZE size, void* mem);
            ~PoolAllocator();

            void* Allocate(SIZE size, U8 alignment) override;

            void Deallocate(void* p) override;

        private:
            PoolAllocator(const PoolAllocator&); //Prevent copies because it might cause errors
            PoolAllocator& operator=(const PoolAllocator&);

            SIZE     mObjectSize;
            U8         mObjectAlign;

            void**     mFreeList;
        };
    }
}

#endif