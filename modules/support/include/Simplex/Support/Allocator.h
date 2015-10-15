#ifndef SIMPLEX_SUPPORT_ALLOCATOR_H
#define SIMPLEX_SUPPORT_ALLOCATOR_H

#include <Simplex/Support/TypeDefs.h>

namespace Simplex
{
    namespace Support
    {
        class Allocator
        {
        public:
            static const U32 DEFAULT_ALIGN = 4;

            Allocator() {}
            virtual ~Allocator() {}

            virtual void* Allocate(U32 size, U32 align = DEFAULT_ALIGN) = 0;
            virtual void Deallocate(void *p) = 0;
            virtual U32 AllocatedSize(void *p) = 0;
            virtual U64 TotalReserved() = 0;
            virtual U64 TotalAllocated() = 0;
            virtual U64 TotalAvailable() = 0;

        private:
            Allocator(const Allocator& other);
            Allocator& operator=(const Allocator& other);
        };
    }
}

#endif
