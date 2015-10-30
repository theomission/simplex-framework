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

            void SetUICallback( void (*callback) (void*), void* metadata );

        private:
            static Subsystem* mInstance;
            Subsystem();

            Support::DoublyLinkedList* mWidgets;

            void (*mUICallback) (void*) = 0;
            void* mMetadata = 0;

        };
    }
}
#endif