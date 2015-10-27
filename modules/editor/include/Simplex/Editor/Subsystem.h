#ifndef SIMPLEX_EDITOR_SUBSYSTEM_H
#define SIMPLEX_EDITOR_SUBSYSTEM_H

#include <Simplex/Support/Subsystem.h>
#include <Simplex/Support/DoublyLinkedList.h>
#include <Simplex/Editor/UI/Widget.h>
namespace Simplex
{
    namespace Editor
    {
        class Subsystem : public Simplex::Support::Subsystem
        {
        public:
            static Subsystem* Instance();

            virtual void Startup() override;
            virtual void Update() override;
            virtual void Shutdown() override;

            void SetUICallback( void (*callback)() );

        private:
            static Subsystem* mInstance;
            Subsystem();

            Support::DoublyLinkedList* mWidgets;

            void (*mUICallback) () = 0;

        };
    }
}
#endif