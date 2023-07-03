#pragma once
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// std
#include <utility>

class Window
{
public:
    Window();
    ~Window();

    static std::pair<const char **, uint32_t> GetInstanceExtensions();
    GLFWwindow *GetWindow() const { return m_window; };

private:
    GLFWwindow *m_window;
};