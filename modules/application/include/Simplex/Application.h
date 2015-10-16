#ifndef SIMPLEX_APPLICATION_H
#define SIMPLEX_APPLICATION_H

#include <Simplex/Support/Allocator.h>
#include <Simplex/Support/Globals.h>

using namespace Simplex::Support;

namespace Simplex
{
    class Application
    {
    public:
        virtual void AllocateMemory( U32 size );
        virtual void Startup();
        virtual void Run();
        virtual void Shutdown();
    private:

        U32 mMemoryToAllocate = 1000 * 1024 * 1024; // Defaults to 1GB
        Allocator* mDefaultAllocator = 0;

    };

}
#endif