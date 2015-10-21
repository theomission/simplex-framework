#include <Simplex/Support/Assert.h>
#include <Simplex/Support/LinearAllocator.h>
#include <Simplex/Support/PointerMath.h>

namespace Simplex
{
    namespace Support
    {
        LinearAllocator::LinearAllocator(SIZE size, void* start) : Allocator(size, start), mCurrentPosition(start)
        {
            ASSERT(size > 0);
        }

        LinearAllocator::~LinearAllocator()
        {
            mCurrentPosition = nullptr;
        }

        void* LinearAllocator::Allocate(SIZE size, U8 align)
        {
            ASSERT(size != 0);

            U8 adjustment =  PointerMath::AlignForwardAdjustment(mCurrentPosition, align);

            if(mUsedMemory + adjustment + size > mSize)
                return nullptr;

            UPTR aligned_address = (UPTR)mCurrentPosition + adjustment;

            mCurrentPosition = (void*)(aligned_address + size);

            mUsedMemory += size + adjustment;
            mAllocationCount++;

            return (void*)aligned_address;
        }

        void LinearAllocator::Clear()
        {
            mAllocationCount     = 0;
            mUsedMemory          = 0;
            mCurrentPosition     = mStart;
        }

    }
}