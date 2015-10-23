#ifndef SIMPLEX_SUPPORT_LINEAR_ALLOCATOR_H
#define SIMPLEX_SUPPORT_LINEAR_ALLOCATOR_H

#include <Simplex/Support/Allocator.h>

namespace Simplex
{
    namespace Support
    {
        class LinearAllocator : public Allocator
        {
        public:
            LinearAllocator(SIZE size, void* start);
            ~LinearAllocator();

            void* Allocate(SIZE size, U8 align) override;
            void Clear();

            // void deallocate(void* p) override;

        private:
            LinearAllocator(const LinearAllocator&); //Prevent copies because it might cause errors
            LinearAllocator& operator=(const LinearAllocator&);

            void* mCurrentPosition;
        };
    }
}
#endif