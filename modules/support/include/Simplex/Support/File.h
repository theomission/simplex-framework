#ifndef SIMPLEX_SUPPORT_FILE_H
#define SIMPLEX_SUPPORT_FILE_H

#include <Simplex/Support/TypeDefs.h>
#include <Simplex/Support/Allocator.h>

namespace Simplex
{
    namespace Support
    {
        namespace File
        {
            // TODO(francisco): Implement an async version of this.
            // TODO(francisco): Use specific allocator to allow subsystems to reserve the memory.
            void* Read(char* filename, Allocator* allocator);
            void Write(char* filename, SIZE size, void* memory);

        }
    }
}

#endif