#include <Simplex/Testing.h>
#include <Simplex/Support/LinkedListAllocator.h>
#include <Simplex/Support/File.h>

using namespace Simplex::Support;

class SimplexSupportFile : public ::testing::Test {
    public:
     protected:
      virtual void SetUp()
      {
        int size = 1 * 1024 * 1024; // 1MB
        mMemory = malloc(size);
        mAllocator = new LinkedListAllocator(size, mMemory);
      };

      virtual void TearDown()
      {
        mAllocator->~LinkedListAllocator();
        delete(mAllocator);
        free(mMemory);
      };

      void* mMemory;
      LinkedListAllocator* mAllocator;
};

TEST_F( SimplexSupportFile, ReadsAndWrites )
{
    char* filename = "mock_file.txt";
    char content[] = "hi!";

    File::Write(filename, sizeof(content), (void*)content );

    char* file_content = (char*)File::Read(filename, mAllocator);
    ASSERT_EQ(*file_content, *content);
    mAllocator->Deallocate(file_content);
}