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

            virtual void Startup() override;
            virtual void Update() override;
            virtual void Shutdown() override;

            ~Subsystem();

            Adapter* Adapter = 0;
        private:
            static Subsystem* mInstance;
            Subsystem();
        };
    }
}

#endif