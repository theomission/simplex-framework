#ifndef SIMPLEX_SUPPORT_PROXY_ALLOCATOR_H
#define SIMPLEX_SUPPORT_PROXY_ALLOCATOR_H

#include <Simplex/Support/Allocator.h>

namespace Simplex
{
    namespace Support
    {
        class ProxyAllocator : public Allocator
        {
        public:
            ProxyAllocator(Allocator& allocator);
            ~ProxyAllocator();

            void* Allocate(SIZE size, U8 alignment) override;

            void Deallocate(void* p) override;

        private:
            ProxyAllocator(const ProxyAllocator&); //Prevent copies because it might cause errors
            ProxyAllocator& operator=(const ProxyAllocator&);

            Allocator& mAllocator;
        };
    }
}

#endif