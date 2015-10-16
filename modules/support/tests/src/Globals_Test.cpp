#include <Simplex/Testing.h>
#include <Simplex/Support/Globals.h>

using namespace Simplex::Support;

TEST ( SimplexCoreAdapter, IsASingleton )
{
    EXPECT_TRUE ( Globals::Instance() != NULL );
}