#ifndef SIMPLEX_GRAPHICS_SUBSYSTEM_H
#define SIMPLEX_GRAPHICS_SUBSYSTEM_H

#include <Simplex/Support/Subsystem.h>
#include <Simplex/Graphics/Adapter.h>
#include <Simplex/Support/Globals.h>

using namespace Simplex;

namespace Simplex
{
    namespace Graphics
    {
        class Subsystem : public Simplex::Support::Subsystem
        {
        public:
            static Subsystem* Instance();
            static void Destroy();

            virtual void Startup() override;
            virtual void Update() override;
            virtual void Shutdown() override;

            ~Subsystem();

            Adapter* Adapter = 0;
        private:
            void* mMemory;
            static Subsystem* mInstance;
            Subsystem();
        };
    }
}

#endif