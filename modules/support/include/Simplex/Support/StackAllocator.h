#ifndef SIMPLEX_SUPPORT_STACK_ALLOCATOR_H
#define SIMPLEX_SUPPORT_STACK_ALLOCATOR_H

#include <Simplex/Support/Allocator.h>

namespace Simplex
{
    namespace Support
    {
        class StackAllocator : public Allocator
        {
        public:
            StackAllocator(U64 size);
            ~StackAllocator();
            void* Allocate(U32 size, U32 align = DEFAULT_ALIGN);
            void Deallocate(void *p);
            U32 AllocatedSize(void *p);
            U64 TotalReserved();
            U64 TotalAllocated();
            U64 TotalAvailable();
        private:
            char* mPool;
            char* mCurrentStackPosition = 0;

            U64 mSize;
        };
    }
}
#endif