#ifndef SIMPLEX_EDITOR_SUBSYSTEM_H
#define SIMPLEX_EDITOR_SUBSYSTEM_H

#include <Simplex/Support/Subsystem.h>

namespace Simplex
{
    namespace Editor
    {
        class Subsystem : public Simplex::Support::Subsystem
        {
        public:
            static Subsystem* Instance();

            virtual void Startup() override;
            virtual void Update() override;
            virtual void Shutdown() override;

        private:
            static Subsystem* mInstance;
            Subsystem();
        };
    }
}
#endif