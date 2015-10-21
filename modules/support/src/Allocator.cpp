#include <Simplex/Support/Assert.h>
#include <Simplex/Support/Allocator.h>

namespace Simplex
{
    namespace Support
    {
        Allocator::Allocator( SIZE size, void* start ) : mSize(size), mStart(start), mUsedMemory(0), mAllocationCount(0)
        {
        }

        Allocator::~Allocator()
        {
            ASSERT(mAllocationCount == 0 && mUsedMemory == 0);
            mStart = nullptr;
            mSize   = 0;
        }

        void* Allocator::GetStartAddress()
        {
            return mStart;
        }

        SIZE Allocator::GetSize()
        {
            return mSize;
        }

        SIZE Allocator::GetUsedMemory()
        {
            return mUsedMemory;
        }

        SIZE Allocator::GetAllocationCount()
        {
            return mAllocationCount;
        }
    }
}