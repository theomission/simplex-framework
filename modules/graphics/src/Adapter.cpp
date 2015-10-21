#include <Simplex/Graphics/Adapter.h>
#include <assert.h>
#include <stdio.h>

// TODO: Add GLFW error handling when implementing global error handling

static void SimplexGLFWKeyCallback ( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        glfwSetWindowShouldClose ( window, GL_TRUE );
}

static void SimplexGLFWErrorCallback ( int error, const char* description )
{
    printf("%s", description);
    assert(false);
}

namespace Simplex
{
    namespace Graphics
    {

        void Adapter::Startup(U16 width, U16 height, bool fullscreen)
        {
            InitializeGLFW(width, height, fullscreen);
        }

        void Adapter::Shutdown()
        {
            glfwTerminate ();
        }

        void Adapter::InitializeGLFW(U16 width, U16 height, bool fullscreen)
        {
            glfwInit();

            glfwSetErrorCallback ( SimplexGLFWErrorCallback );

            GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor () : NULL;
            glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_API );
            glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
            glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            #if __OSX__
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            #endif

            Window = glfwCreateWindow ( width, height, "Application", monitor, NULL );

            glfwMakeContextCurrent ( Window );

            glfwSetKeyCallback ( Window, SimplexGLFWKeyCallback );
        }

        bool Adapter::ShouldShutdown()
        {
            return glfwWindowShouldClose(Window);
        }

        void Adapter::SwapBuffers()
        {
            glfwSwapBuffers(Window);
            glfwPollEvents();

            // Rendering
            int display_w, display_h;
            glfwGetFramebufferSize(Window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.5, 0.5, 0.5, 1);
            glClear(GL_COLOR_BUFFER_BIT);

        }
    }
}