#include <stdio.h>
#include <Simplex/Application.h>
#include <Simplex/Support/Globals.h>
#include <Simplex/Support/LinearAllocator.h>
#include <GLFW/glfw3.h>

using namespace Simplex;
using namespace Simplex::Support;
namespace Simplex
{
    void Application::AllocateMemory( U32 size )
    {
        mMemoryToAllocate = size;
    }

    void Application::Startup ()
    {
        StartupAllocator();

        Graphics::Subsystem::Instance()->Startup();
        Editor::Subsystem::Instance()->Startup();
    }

    void Application::StartupAllocator()
    {
        void* mAllocationStartAddress = malloc(mMemoryToAllocate);
        mDefaultAllocator = new Support::LinearAllocator(mMemoryToAllocate, mAllocationStartAddress);
        Support::Globals::Instance()->Allocator = mDefaultAllocator;
    }

    void Application::Run ()
    {   /* Loop until the user closes the window */
        while (!Globals::Instance()->ShouldShutdown)
        {
            FrameStep();

            Editor::Subsystem::Instance()->Update();
            Graphics::Subsystem::Instance()->Update();
        }
    }

    void Application::Shutdown ()
    {
        Editor::Subsystem::Instance()->Shutdown();
        Graphics::Subsystem::Instance()->Shutdown();
    }

}


