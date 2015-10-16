#include <Simplex/Support/Globals.h>
#include <Simplex/Support/StackAllocator.h>
#include <Simplex/Testing.h>

using namespace Simplex::Support;

int main ( int argc, char **argv )
{
    // Allocate 100MB and send it to the heap
    StackAllocator* allocator = new StackAllocator(100 * 1024 * 1024);

    // Set Allocator as default allocator
    Globals.allocator = (Allocator*)allocator;

    Simplex::Testing::Runner testRunner = Simplex::Testing::Runner ( argc, argv );
    return testRunner.Start ();
}
