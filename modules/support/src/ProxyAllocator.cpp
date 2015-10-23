#include <Simplex/Support/Assert.h>
#include <Simplex/Support/ProxyAllocator.h>

namespace Simplex
{
    namespace Support
    {
        ProxyAllocator::ProxyAllocator(Allocator& allocator)
            : Allocator(allocator.GetSize(), allocator.GetStartAddress()), mAllocator(allocator)
        {

        }

        ProxyAllocator::~ProxyAllocator()
        {

        }

        void* ProxyAllocator::Allocate(SIZE size, U8 alignment)
        {
            ASSERT(size != 0);
            mAllocationCount++;

            SIZE mem = mAllocator.GetUsedMemory();

            void* p = mAllocator.Allocate(size, alignment);

            mUsedMemory += mAllocator.GetUsedMemory() - mem;

            return p;
        }

        void ProxyAllocator::Deallocate(void* p)
        {
            mAllocationCount--;

            size_t mem = mAllocator.GetUsedMemory();

            mAllocator.Deallocate(p);

            mUsedMemory -= mem - mAllocator.GetUsedMemory();
        }
    }
}