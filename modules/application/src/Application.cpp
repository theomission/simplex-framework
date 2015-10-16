#include <Simplex/Application.h>
#include <Simplex/Support/Globals.h>
#include <Simplex/Support/StackAllocator.h>
using namespace Simplex::Support;

namespace Simplex
{
    void Application::AllocateMemory( U32 size )
    {
        mMemoryToAllocate = size;
    }

    void Application::Startup ()
    {
        mDefaultAllocator = new StackAllocator(mMemoryToAllocate);
        Globals::Instance()->allocator = mDefaultAllocator;
    }

    void Application::Run ()
    {}

    void Application::Shutdown ()
    {}
}
