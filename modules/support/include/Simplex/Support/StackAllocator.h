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
            StackAllocator(SIZE size, void* start);
            ~StackAllocator();

            void* Allocate(SIZE size, U8 alignment) override;

            void Deallocate(void* p) override;

        private:
            StackAllocator(const StackAllocator&);
            StackAllocator& operator=(const StackAllocator&);

            struct AllocationHeader
            {
                #if __DEBUG__
                void* PreviousAddress;
                #endif
                U8 Adjustment;
            };

            #if __DEBUG__
            void* mPreviousPosition;
            #endif

            void*  mCurrentPosition;

        };
    }
}
#endif