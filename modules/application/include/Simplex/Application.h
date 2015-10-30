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
        Support::Allocator* mDefaultAllocator = 0;
        void* mAllocationStartAddress;
        Support::DoublyLinkedList* mSubsystems = 0;

    private:

        void StartupSubsystems();
        void UpdateSubsystems();
        void ShutdownSubsystems();
        void SetupLinkedListForSubsystems();

        U32 mSubsystemCount = 1;

    };




}
#endif