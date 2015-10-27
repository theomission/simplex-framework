#ifndef MOCK_WIDGET_H
#define MOCK_WIDGET_H

#include <Simplex/Editor/UI/Widget>

class MockWidget : Simplex::Editor::UI::Widget
{
public:
    override void Update ()
    {
        UpdateCalled = true;
    };

    bool UpdateCalled = false;
};
#endif