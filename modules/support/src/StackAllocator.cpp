#include <Simplex/Support/Assert.h>
#include <Simplex/Support/StackAllocator.h>
#include <Simplex/Support/PointerMath.h>

namespace Simplex
{
    namespace Support
    {
        StackAllocator::StackAllocator(SIZE size, void* start)
            : Allocator(size, start), mCurrentPosition(start)
        {
            ASSERT(size > 0);

            #if __DEBUG__
            mPreviousPosition    = nullptr;
            #endif
        }

        StackAllocator::~StackAllocator()
        {
            #if __DEBUG__
            mPreviousPosition      = nullptr;
            #endif

            mCurrentPosition       = nullptr;
        }

        void* StackAllocator::Allocate(SIZE size, U8 alignment)
        {
            ASSERT(size != 0);

            U8 adjustment = PointerMath::AlignForwardAdjustmentWithHeader(
                mCurrentPosition, alignment, sizeof(AllocationHeader));

            if(mUsedMemory + adjustment + size > mSize)
                return nullptr;

            void* aligned_address = PointerMath::Add(
                mCurrentPosition, adjustment);

            AllocationHeader* header = (AllocationHeader*)(
                PointerMath::Subtract(aligned_address, sizeof(AllocationHeader))
            );

            header->Adjustment   = adjustment;

            #if __DEBUG__
            header->PreviousAddress = mPreviousPosition;
            mPreviousPosition       = aligned_address;
            #endif

            mCurrentPosition = PointerMath::Add(aligned_address, size);

            mUsedMemory += size + adjustment;
            mAllocationCount++;

            return aligned_address;
        }

        void StackAllocator::Deallocate(void* p)
        {
            #if __DEBUG__
            ASSERT( p == mPreviousPosition );
            #endif

            AllocationHeader* header = (AllocationHeader*)(
                PointerMath::Subtract(p, sizeof(AllocationHeader))
            );

            mUsedMemory -= (UPTR)mCurrentPosition -
                (UPTR)p + header->Adjustment;

            mCurrentPosition = PointerMath::Subtract(p, header->Adjustment);

            #if _DEBUG
            mPreviousPosition = header->PreviousAddress;
            #endif

            mAllocationCount--;
        }
    }
}
