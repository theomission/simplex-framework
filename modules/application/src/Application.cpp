#include <stdio.h>
#include <Simplex/Application.h>
#include <Simplex/Support/Globals.h>
#include <Simplex/Support/LinearAllocator.h>
#include <Simplex/Graphics.h>
#include <Simplex/Editor.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

using namespace Simplex;
using namespace Simplex::Support;
namespace Simplex
{
    void Application::AllocateMemory( U32 size )
    {
        void* mAllocationStartAddress = malloc(size);
        mDefaultAllocator = new Support::LinearAllocator(size, mAllocationStartAddress);
        Support::Globals::Instance()->Allocator = mDefaultAllocator;
    }

    void Application::Startup()
    {
        StartupSubsystems();
    }

    void Application::StartupSubsystems()
    {
        DoublyLinkedList::Node* subsystem = mSubsystems->First();

        while(subsystem != nullptr)
        {
            ((Subsystem*)subsystem->Value)->Startup();
            subsystem = subsystem->Next;
        }
    }
    void Application::Run()
    {   /* Loop until the user closes the window */
        while (!Globals::Instance()->ShouldShutdown)
        {
            UpdateSubsystems();
            FrameStep();
        }
    }

    void Application::UpdateSubsystems()
    {
        DoublyLinkedList::Node* subsystem = mSubsystems->First();

        while(subsystem != nullptr)
        {
            ((Subsystem*)subsystem->Value)->Update();
            subsystem = subsystem->Next;
        }
    }

    void Application::Shutdown()
    {
        ShutdownSubsystems();
    }

    void Application::ShutdownSubsystems()
    {
        if(mSubsystems)
        {
            DoublyLinkedList::Node* subsystem = mSubsystems->First();

            while(subsystem != nullptr)
            {
                ((Subsystem*)subsystem->Value)->Shutdown();
                subsystem = subsystem->Next;
            }
        }
    }

    void Application::SetSubsystemCount(U32 count)
    {
        mSubsystemCount = count;
        SetupLinkedListForSubsystems();
    }

    void Application::SetupLinkedListForSubsystems()
    {
        void* memory = mDefaultAllocator->Allocate(sizeof(DoublyLinkedList), alignof(DoublyLinkedList));
        mSubsystems = new(memory) DoublyLinkedList(mSubsystemCount);
    }



    void Application::AddSubsystem(Support::Subsystem* subsystem)
    {
        mSubsystems->PushBack(subsystem);
    }

}


