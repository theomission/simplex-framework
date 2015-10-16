#include <Simplex/Support/Globals.h>
#include <Simplex/Support/StackAllocator.h>
#include <Simplex/Testing.h>

using namespace Simplex::Support;

int main ( int argc, char **argv )
{
    Simplex::Testing::Runner testRunner;

    testRunner.SetArguments(argc, argv);

    testRunner.Startup();
    testRunner.Run();
    testRunner.Shutdown();

    return testRunner.GetTestResult();
}
