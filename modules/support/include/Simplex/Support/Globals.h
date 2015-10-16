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

            Simplex::Support::Allocator* allocator = 0;

        private:
            Globals() {};

            static Globals* mInstance;
        };
    }
}

#endif