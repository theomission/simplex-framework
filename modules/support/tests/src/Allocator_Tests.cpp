#include <Simplex/Testing.h>
#include <Simplex/Support/Allocator.h>

using namespace Simplex::Support;

class AllocatorMock : public Simplex::Support::Allocator
{

public:
  AllocatorMock ( SIZE size, void* start ) : Allocator(size, start) {};

  virtual void* Allocate(SIZE size, U8 alignment = 4) override
  {
    mUsedMemory = size + (SIZE)alignment;
    mAllocationCount++;
    return nullptr;
  };

  virtual void Deallocate(void* ptr) override
  {
    mUsedMemory = 0;
    mAllocationCount = 0;
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

TEST ( SimplexSupportAllocator, GetUsedMemoryReturnsMemoryUsed )
{
  UPTR ptr = 10;
  AllocatorMock a(5, (void*)(ptr));
  a.Allocate(sizeof(int), alignof(int));
  ASSERT_EQ ( a.GetUsedMemory(), 8 );
  a.Deallocate(0);
}

TEST ( SimplexSupportAllocator, GetAllocationCountReturnsCorrectly )
{
  UPTR ptr = 10;
  AllocatorMock a(5, (void*)(ptr));
  a.Allocate(sizeof(int), alignof(int));
  ASSERT_EQ ( a.GetAllocationCount(), 1 );
  a.Deallocate(0);
}
