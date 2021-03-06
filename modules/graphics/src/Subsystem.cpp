#include <Simplex/Support.h>
#include <Simplex/Graphics/Subsystem.h>

namespace Simplex
{
    namespace Graphics
    {
        Subsystem* Subsystem::mInstance = nullptr;

        Subsystem* Subsystem::Instance()
        {
                if(mInstance == NULL)
                {
                    void* memory = Support::Globals::Instance()->Allocator->Allocate(sizeof(Subsystem), alignof(Subsystem));
                    mInstance = new(memory) Subsystem();
                }
                return mInstance;
        }

        void Subsystem::Destroy()
        {
            Subsystem::Instance()->~Subsystem();
             Support::Globals::Instance()->Allocator->Deallocate(Subsystem::Instance());
             mInstance = nullptr;
        }

        Subsystem::Subsystem()
        {}

        Subsystem::~Subsystem()
        {
        }

        void Subsystem::Startup()
        {
            void* memory = Support::Globals::Instance()->Allocator->Allocate(sizeof(Simplex::Graphics::Adapter),alignof(Simplex::Graphics::Adapter));
            Adapter = new(memory) Graphics::Adapter();
            Adapter->Startup(1920,1080, true);
            Initialized = true;
        }

        void Subsystem::Update()
        {
            Adapter->SwapBuffers();
        }

        void Subsystem::Shutdown()
        {
            Adapter->Shutdown();
            Support::Globals::Instance()->Allocator->Deallocate(Adapter);
            Initialized = false;
        }
    }
}