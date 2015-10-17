#include <Simplex/Testing.h>
#include <Simplex/Support/Globals.h>

using namespace Simplex::Support;

TEST ( SimplexGlobals, IsASingleton )
{
    EXPECT_TRUE ( Globals::Instance() != NULL );
}

TEST ( SimplexGlobals, ContainsBoolCalledShouldShutdown )
{
    EXPECT_EQ ( Globals::Instance()->ShouldShutdown, false );
}