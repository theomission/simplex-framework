#ifndef SIMPLEX_SUPPORT_POINTER_MATH_H
#define SIMPLEX_SUPPORT_POINTER_MATH_H

// TODO: TEST THIS!!!
namespace PointerMath
{
    inline void* AlignForward(void* address, U8 alignment)
    {
        return (void*)( ( reinterpret_cast<UPTR>(address) + static_cast<UPTR>(alignment-1) ) & static_cast<UPTR>(~(alignment-1)) );
    }

    inline const void* AlignForward(const void* address, U8 alignment)
    {
        return (void*)( ( reinterpret_cast<UPTR>(address) + static_cast<UPTR>(alignment-1) ) & static_cast<UPTR>(~(alignment-1)) );
    }

    inline void* AlignBackward(void* address, U8 alignment)
    {
        return (void*)( reinterpret_cast<UPTR>(address) & static_cast<UPTR>(~(alignment-1)) );
    }

    inline const void* AlignBackward(const void* address, U8 alignment)
    {
        return (void*)( reinterpret_cast<UPTR>(address) & static_cast<UPTR>(~(alignment-1)) );
    }

    inline U8 AlignForwardAdjustment(const void* address, U8 alignment)
    {
        U8 adjustment =  alignment - ( reinterpret_cast<UPTR>(address) & static_cast<UPTR>(alignment-1) );

        if(adjustment == alignment)
            return 0; //already aligned

        return adjustment;
    }

    inline U8 AlignForwardAdjustmentWithHeader(const void* address, U8 alignment, U8 headerSize)
    {
        U8 adjustment =  AlignForwardAdjustment(address, alignment);

        U8 neededSpace = headerSize;

        if(adjustment < neededSpace)
        {
            neededSpace -= adjustment;

            //Increase adjustment to fit header
            adjustment += alignment * (neededSpace / alignment);

            if(neededSpace % alignment > 0)
                adjustment += alignment;
        }

        return adjustment;
    }

    inline U8 AlignBackwardAdjustment(const void* address, U8 alignment)
    {
        U8 adjustment =  reinterpret_cast<UPTR>(address) & static_cast<UPTR>(alignment-1);

        if(adjustment == alignment)
            return 0; //already aligned

        return adjustment;
    }

    inline void* Add(void* p, size_t x)
    {
        return (void*)( reinterpret_cast<UPTR>(p) + x);
    }

    inline const void* Add(const void* p, size_t x)
    {
        return (const void*)( reinterpret_cast<UPTR>(p) + x);
    }

    inline void* Subtract(void* p, size_t x)
    {
        return (void*)( reinterpret_cast<UPTR>(p) - x);
    }

    inline const void* Subtract(const void* p, size_t x)
    {
        return (const void*)( reinterpret_cast<UPTR>(p) - x);
    }

}


#endif