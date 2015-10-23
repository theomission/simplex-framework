#include <Simplex/Support/Assert.h>
#include <Simplex/Support/PoolAllocator.h>
#include <Simplex/Support/PointerMath.h>


namespace Simplex
{
    namespace Support
    {
        PoolAllocator::PoolAllocator(SIZE objectSize, U8 objectAlign, SIZE size, void* mem)
            : Allocator(size, mem), mObjectSize(objectSize), mObjectAlign(objectAlign)
        {
            ASSERT(objectSize >= sizeof(void*));

            //Calculate adjustment needed to keep object correctly aligned
            U8 adjustment = PointerMath::AlignForwardAdjustment(mem, objectAlign);

            mFreeList = (void**)PointerMath::Add(mem, adjustment);

            SIZE numObjects = (size-adjustment)/objectSize;

            void** p = mFreeList;

            //Initialize free blocks list
            for(SIZE i = 0; i < numObjects-1; i++)
            {
                *p = PointerMath::Add(p, objectSize );
                p = (void**) *p;
            }

            *p = nullptr;
        }

        PoolAllocator::~PoolAllocator()
        {
            mFreeList = nullptr;
        }

        void* PoolAllocator::Allocate(SIZE size, U8 alignment)
        {
            ASSERT(size == mObjectSize && alignment == mObjectAlign);

            if(mFreeList == nullptr)
                return nullptr;

            void* p = mFreeList;

            mFreeList = (void**)(*mFreeList);

            mUsedMemory += size;
            mAllocationCount++;

            return p;
        }

        void PoolAllocator::Deallocate(void* p)
        {
            *((void**)p) = mFreeList;

            mFreeList = (void**)p;

            mUsedMemory -= mObjectSize;
            mAllocationCount--;
        }
    }
}