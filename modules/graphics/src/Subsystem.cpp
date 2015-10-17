#include <Simplex/Support.h>
#include <Simplex/Graphics/Subsystem.h>


namespace Simplex
{
    namespace Graphics
    {
        Subsystem* Subsystem::mInstance = NULL;

        Subsystem* Subsystem::Instance()
        {
                if(mInstance == NULL)
                {
                    void* memory = Support::Globals::Instance()->Allocator->Allocate(sizeof(Subsystem), alignof(Subsystem));
                    mInstance = new(memory) Subsystem();
                }
                return mInstance;
        }

        Subsystem::Subsystem()
        {}

        void Subsystem::Startup()
        {
            void * memory = Support::Globals::Instance()->Allocator->Allocate(sizeof(Simplex::Graphics::Adapter),alignof(Simplex::Graphics::Adapter));
            Adapter = new(memory) Graphics::Adapter();
            Adapter->Startup(1920,1080, false);
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