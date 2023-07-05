#pragma once
#include "Window.hpp"
#include "GuiRenderer.hpp"

class Application
{
public:
    Application();
    ~Application();

    void Run();

private:
    Window *m_window;
    GuiRenderer *m_guiRenderer;
};