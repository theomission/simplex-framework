#ifndef SIMPLEX_APPLICATION_H
#define SIMPLEX_APPLICATION_H

#include <Simplex/Support/Allocator.h>
#include <Simplex/Support/Globals.h>
#include <Simplex/Support/Subsystem.h>
#include <Simplex/Support/DoublyLinkedList.h>

using namespace Simplex;

namespace Simplex
{
    class Application
    {
    public:
        virtual void AllocateMemory( U32 size );
        virtual void Startup();
        virtual void Run();
        virtual void Shutdown();

        void SetSubsystemCount(U32 count);
        void AddSubsystem(Support::Subsystem* subsystem);

    protected:
        virtual void FrameStep() = 0;

    private:

        U32 mMemoryToAllocate = 1000 * 1024 * 1024; // Defaults to 1GB
        Support::Allocator* mDefaultAllocator = 0;
        void* mAllocationStartAddress;

        void StartupSubsystems();
        void UpdateSubsystems();
        void ShutdownSubsystems();
        void SetupLinkedListForSubsystems();

        U32 mSubsystemCount = 1;
        Support::DoublyLinkedList* mSubsystems;

    };




}
#endif