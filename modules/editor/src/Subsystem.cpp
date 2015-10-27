#include <Simplex/Support.h>
// #include <Simplex/Graphics/Subsystem.h>
#include <Simplex/Editor/Subsystem.h>
#include <Simplex/Editor/UI.h>
#include <Simplex/Editor/Widgets.h>
#include <Simplex/Graphics.h>

using namespace Simplex;

namespace Simplex
{
    namespace Editor
    {
        Subsystem* Subsystem::mInstance = NULL;

        Subsystem* Subsystem::Instance()
        {
                if(mInstance == NULL)
                {
                    void* memory = Support::Globals::Instance()->Allocator->Allocate(sizeof(Subsystem), alignof(Subsystem));
                    mInstance = new(memory) Subsystem();
                }
                return mInstance;
        }

        Subsystem::Subsystem()
        {}

        void Subsystem::Startup()
        {
            gl3wInit();
            ImGui_ImplGlfwGL3_Init(Graphics::Subsystem::Instance()->Adapter->Window, true);


            Initialized = true;
        }

        void Subsystem::Update()
        {
            bool show_test_window = true;
            // bool show_another_window = false;
            ImGui_ImplGlfwGL3_NewFrame();

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            if(mUICallback != nullptr)
                mUICallback();


            // Show Widgets

            // 1. Show a simple window
            // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"

            // // 2. Show another simple window, this time using an explicit Begin/End pair
            // if (show_another_window)
            // {
            //     ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
            //     ImGui::Begin("Another Window", &show_another_window);
            //     ImGui::Text("Hello");
            //     ImGui::End();
            // }

            // // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
            // if (show_test_window)
            // {
            //     ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
            // ImGui::ShowTestWindow(&show_test_window);
            // }
            ImGui::Render();

        }

        void Subsystem::Shutdown()
        {
            ImGui_ImplGlfwGL3_Shutdown();
            Initialized = false;
        }

        void Subsystem::SetUICallback( void (*callback)() )
        {
            mUICallback = callback;
        }
    }
}