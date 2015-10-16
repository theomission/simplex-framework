#include <Simplex/Support/Globals.h>

namespace Simplex
{
    namespace Support
    {
        Globals* Globals::mInstance = 0;

        Globals* Globals::Instance()
        {
            if(mInstance == NULL)
                mInstance = new Globals;

            return mInstance;
        }
    }
}