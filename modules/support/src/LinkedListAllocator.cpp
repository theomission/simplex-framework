#include <Simplex/Support/LinkedListAllocator.h>
#include <Simplex/Support/PointerMath.h>
#include <Simplex/Support/Assert.h>
namespace Simplex
{
    namespace Support
    {
        LinkedListAllocator::LinkedListAllocator(SIZE size, void* start)
            : Allocator(size, start), mFreeBlocks((FreeBlock*)start)
        {
            ASSERT(size > sizeof(FreeBlock));

            mFreeBlocks->Size  = size;
            mFreeBlocks->Next = nullptr;
        }

        LinkedListAllocator::~LinkedListAllocator()
        {
            mFreeBlocks        = nullptr;
        }

        void* LinkedListAllocator::Allocate(SIZE size, U8 alignment)
        {
            ASSERT(size != 0 && alignment != 0);

            FreeBlock* prev_free_block = nullptr;
            FreeBlock* free_block     = mFreeBlocks;

            while(free_block != nullptr)
            {
                //Calculate adjustment needed to keep object correctly aligned
                U8 adjustment = PointerMath::AlignForwardAdjustmentWithHeader(free_block, alignment, sizeof(AllocationHeader));

                SIZE total_size = size + adjustment;

                //If allocation doesn't fit in this FreeBlock, try the next
                if(free_block->Size < total_size)
                {
                    prev_free_block = free_block;
                    free_block = free_block->Next;
                    continue;
                }

                static_assert(sizeof(AllocationHeader) >= sizeof(FreeBlock), "sizeof(AllocationHeader) < sizeof(FreeBlock)");

                //If allocations in the remaining memory will be impossible
                if(free_block->Size - total_size <= sizeof(AllocationHeader))
                {
                    //Increase allocation size instead of creating a new FreeBlock
                    total_size = free_block->Size;

                    if(prev_free_block != nullptr)
                        prev_free_block->Next = free_block->Next;
                    else
                        mFreeBlocks = free_block->Next;
                }
                else
                {
                    //Else create a new FreeBlock containing remaining memory
                    FreeBlock* next_block = (FreeBlock*)( PointerMath::Add(free_block, total_size) );
                    next_block->Size = free_block->Size - total_size;
                    next_block->Next = free_block->Next;

                    if(prev_free_block != nullptr)
                        prev_free_block->Next = next_block;
                    else
                        mFreeBlocks = next_block;
                }

                UPTR aligned_address = (UPTR)free_block + adjustment;

                AllocationHeader* header = (AllocationHeader*)(aligned_address - sizeof(AllocationHeader));
                header->Size             = total_size;
                header->Adjustment       = adjustment;

                mUsedMemory += total_size;
                mAllocationCount++;

                ASSERT(PointerMath::AlignForwardAdjustment((void*)aligned_address, alignment) == 0);

                return (void*)aligned_address;
            }

            //ASSERT(false && "Couldn't find free block large enough!");

            return nullptr;
        }

        void LinkedListAllocator::Deallocate(void* p)
        {
            ASSERT(p != nullptr);

            AllocationHeader* header = (AllocationHeader*)PointerMath::Subtract(p, sizeof(AllocationHeader));

            UPTR   block_start = reinterpret_cast<UPTR>(p) - header->Adjustment;
            SIZE block_size  = header->Size;
            UPTR   block_end   = block_start + block_size;

            FreeBlock* prev_free_block = nullptr;
            FreeBlock* free_block = mFreeBlocks;

            while(free_block != nullptr)
            {
                if( (UPTR) free_block >= block_end )
                    break;

                prev_free_block = free_block;
                free_block = free_block->Next;
            }

            if(prev_free_block == nullptr)
            {
                prev_free_block = (FreeBlock*) block_start;
                prev_free_block->Size = block_size;
                prev_free_block->Next = mFreeBlocks;

                mFreeBlocks = prev_free_block;
            } else if((UPTR) prev_free_block + prev_free_block->Size == block_start)
            {
                prev_free_block->Size += block_size;
            } else
            {
                FreeBlock* temp = (FreeBlock*) block_start;
                temp->Size = block_size;
                temp->Next = prev_free_block->Next;
                prev_free_block->Next = temp;

                prev_free_block = temp;
            }

            if( free_block != nullptr && (UPTR) free_block == block_end)
            {
                prev_free_block->Size += free_block->Size;
                prev_free_block->Next = free_block->Next;
            }

            mAllocationCount--;
            mUsedMemory -= block_size;
        }
    }
}