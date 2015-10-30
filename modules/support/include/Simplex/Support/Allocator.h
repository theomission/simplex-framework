#ifndef SIMPLEX_SUPPORT_ALLOCATOR_H
#define SIMPLEX_SUPPORT_ALLOCATOR_H

#include <Simplex/Support/TypeDefs.h>
#include <Simplex/Support/Assert.h>

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
        // TODO (francisco): Test This

        template<class T> T* allocateArray(Allocator& allocator, SIZE length)
        {
            ASSERT(length != 0);

            U8 headerSize = sizeof(size_t)/sizeof(T);

            if(sizeof(SIZE)%sizeof(T) > 0)
              headerSize += 1;

            //Allocate extra space to store array length in the bytes before the array
            T* p = ( (T*) allocator.Allocate(sizeof(T)*(length + headerSize), __alignof(T)) ) + headerSize;

            *( ((SIZE*)p) - 1 ) = length;

            for(SIZE i = 0; i < length; i++)
                new (&p[i]) T;

            return p;
        }

        template<class T> void deallocateArray(Allocator& allocator, T* array)
        {
            ASSERT(array != nullptr);

            SIZE length = *( ((SIZE*)array) - 1 );

            for(SIZE i = 0; i < length; i++)
                array[i].~T();

            //Calculate how much extra memory was allocated to store the length before the array
            U8 headerSize = sizeof(SIZE)/sizeof(T);

            if(sizeof(SIZE)%sizeof(T) > 0)
                headerSize += 1;

            allocator.Deallocate(array - headerSize);
        }
    }
}



#endif
