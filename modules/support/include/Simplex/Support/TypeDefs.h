#ifndef SIMPLEX_SUPPORT_TYPEDEFS_H
#define SIMPLEX_SUPPORT_TYPEDEFS_H
#include <xmmintrin.h>
#include <new>

#if defined(__OSX__) || defined(__LINUX__)
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