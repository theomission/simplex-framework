#include <Simplex/Testing.h>
#include <Simplex/Graphics/Adapter.h>
#include <GLFW/glfw3.h>

TEST ( SimplexGraphicsAdapter, InheritsFromSimplexSupportAdapter )
{
    Simplex::Graphics::Adapter adapter;
    ASSERT_TRUE ( dynamic_cast< Simplex::Support::Adapter* >( &adapter ) );
}
