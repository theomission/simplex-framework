#ifndef SIMPLEX_SUPPORT_GLOBALS_H
#define SIMPLEX_SUPPORT_GLOBALS_H

#include <Simplex/Support/Allocator.h>
namespace Simplex
{
    namespace Support
    {
        class Globals
        {
        public:
            static Globals* Instance();

            bool ShouldShutdown = false;
            Simplex::Support::Allocator* Allocator = 0;

        private:
            Globals() {};

            static Globals* mInstance;
        };
    }
}

#endif