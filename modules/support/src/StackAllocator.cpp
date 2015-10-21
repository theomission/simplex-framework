#include <Simplex/Support/StackAllocator.h>

namespace Simplex
{
    namespace Support
    {
        struct Metadata
        {
            U32 BlockSize;
        };

        StackAllocator::StackAllocator(U64 size) : mSize(size), Allocator(mSize, mPool)
        {
            mPool = new char[size];
            mCurrentStackPosition = mPool;
        }

        StackAllocator::~StackAllocator()
        {
            delete[] mPool;
        }

        void* StackAllocator::Allocate(U32 size, U32 align)
        {
            mCurrentStackPosition += size;

            Metadata* m = (Metadata*)(mCurrentStackPosition);
            m->BlockSize = size;
            mCurrentStackPosition += sizeof(Metadata);

            return mCurrentStackPosition;
        }

        void StackAllocator::Deallocate(void *p)
        {
            mCurrentStackPosition -= sizeof(Metadata);
            Metadata* m = (Metadata*)(mCurrentStackPosition);
            mCurrentStackPosition -= m->BlockSize;
        }

        U32 StackAllocator::AllocatedSize(void *p)
        {
            return 0;
        }

        U64 StackAllocator::TotalReserved()
        {
            return mSize;
        }

        U64 StackAllocator::TotalAllocated()
        {
            return mCurrentStackPosition - mPool;
        }

        U64 StackAllocator::TotalAvailable()
        {
            return TotalReserved() - TotalAllocated();
        }

    }
}
