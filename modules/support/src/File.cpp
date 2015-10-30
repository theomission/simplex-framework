#include <Simplex/Support/File.h>

#include <stdio.h>

namespace Simplex
{
    namespace Support
    {
        namespace File
        {
            void* Read(char* filename, Allocator* allocator)
            {
                FILE *f = fopen(filename, "rb");

                ASSERT(f != nullptr);

                fseek(f, 0, SEEK_END);
                U32 fsize = ftell(f);
                fseek(f, 0, SEEK_SET);

                void* buffer = allocator->Allocate(fsize);
                fread(buffer, fsize, 1, f);
                fclose(f);

                return buffer;
            }

            void Write(char* filename, SIZE size, void* memory)
            {
                FILE *f;
                f = fopen (filename, "wb");

                ASSERT(f != nullptr);

                fwrite (memory , size, 1, f);
                fclose (f);
            }
        }
    }
}
