#ifndef SIMPLEX_SUPPORT_ALLOCATOR_H
#define SIMPLEX_SUPPORT_ALLOCATOR_H

#include <Simplex/Support/TypeDefs.h>

//  TODO: Add global allocate and allocateArray

namespace Simplex
{
    namespace Support
    {
        class Allocator
        {
        public:
            static const U8 DEFAULT_ALIGN = 4;

            virtual ~Allocator();

            virtual void* Allocate(SIZE size, U8 align = DEFAULT_ALIGN) { return nullptr; };
            virtual void Deallocate(void *p) {};
            virtual U32 AllocatedSize(void *p) { return 0; };
            virtual U64 TotalReserved() { return 0; };
            virtual U64 TotalAllocated() { return 0; };
            virtual U64 TotalAvailable()  { return 0; };


            Allocator ( SIZE size, void* start );

            void* GetStartAddress();
            SIZE GetSize();

            SIZE GetUsedMemory();
            SIZE GetAllocationCount();

        private:
            Allocator(const Allocator& other);
            Allocator& operator=(const Allocator& other);

        protected:
            void* mStart;
            SIZE mSize;

            SIZE mUsedMemory;
            SIZE mAllocationCount;
        };
    }
}



#endif
