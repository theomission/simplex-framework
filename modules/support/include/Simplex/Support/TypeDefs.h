#ifndef SIMPLEX_SUPPORT_TYPEDEFS_H
#define SIMPLEX_SUPPORT_TYPEDEFS_H
#include <xmmintrin.h>
#include <new>
#include <cstdint>

#if defined(__OSX__) || defined(__LINUX__)
typedef             uintptr_t UPTR;
typedef             size_t SIZE;

typedef             char    I8;
typedef             short   I16;
typedef             int     I32;
typedef             long    I64;

typedef unsigned    char    U8;
typedef unsigned    short   U16;
typedef unsigned    int     U32;
typedef unsigned    long    U64;

typedef             float   F32;
typedef             double  F64;

typedef             __m128  VF32;
#endif


#endif