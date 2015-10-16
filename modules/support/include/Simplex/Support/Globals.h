#ifndef SIMPLEX_SUPPORT_GLOBALS_H
#define SIMPLEX_SUPPORT_GLOBALS_H

#include <Simplex/Support/Allocator.h>

struct GlobalsStruct
{
    Simplex::Support::Allocator* allocator;
};

GlobalsStruct Globals;

#endif