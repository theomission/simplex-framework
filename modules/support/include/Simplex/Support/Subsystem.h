#ifndef SIMPLEX_SUPPORT_SUBSYSTEM_ALLOCATOR_H
#define SIMPLEX_SUPPORT_SUBSYSTEM_ALLOCATOR_H

namespace Simplex
{
    namespace Support
    {
        class Subsystem
        {
        public:
            virtual void Startup() = 0;
            virtual void Update() = 0;
            virtual void Shutdown() = 0;

            bool Initialized = false;
        };
    }
}
#endif