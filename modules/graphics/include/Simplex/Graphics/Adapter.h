#ifndef SIMPLEX_GRAPHICS_ADAPTER_H
#define SIMPLEX_GRAPHICS_ADAPTER_H

#include <Simplex/Support.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace Simplex
{
    namespace Graphics
    {
        class Adapter : public Simplex::Support::Adapter
        {
        public:
            void Startup(U16 width, U16 height, bool fullscreen);
            void Shutdown();
            void SwapBuffers();
            bool ShouldShutdown();

            GLFWwindow* Window;

        private:
            void InitializeGLFW(U16 width, U16 height, bool fullscreen);
        };

    }

}
#endif