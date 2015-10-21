#include <Simplex/Testing.h>
#include <Simplex/Support/Allocator.h>

using namespace Simplex::Support;

class AllocatorMock : public Simplex::Support::Allocator
{

public:
  AllocatorMock ( SIZE size, void* start ) : Allocator(size, start) {};

  virtual void* Allocate(SIZE size, U8 alignment = 4) override
  {
    return nullptr;
  };

  virtual void Deallocate(void* ptr) override
  {
  }
};

TEST ( SimplexSupportAllocator, SetsStartPointerCorrectly )
{
  UPTR ptr = 10;
  AllocatorMock a(10, (void*)(ptr));
  ASSERT_EQ (reinterpret_cast<UPTR>(a.GetStartAddress()), 10 );
}

TEST ( SimplexSupportAllocator, SetsSizeCorrectly )
{
  UPTR ptr = 10;
  AllocatorMock a(5, (void*)(ptr));
  ASSERT_EQ ( a.GetSize(), 5 );
}
