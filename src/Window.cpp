#include "Window.hpp"

#include "Log.hpp"

// std
#include <stdexcept>
#include <string>

static void ErrorCallback(int32_t error, const char *description)
{
    Log::Error("GLFW error: ", description, ", ", error, '\n');
    throw std::runtime_error("GLFW error: " + std::to_string(error));
}

Window::Window()
{
    glfwSetErrorCallback(ErrorCallback);
    if (!glfwInit())
        throw std::runtime_error("GLFW: Failed to initialize!");

    // Create window with Vulkan context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_window = glfwCreateWindow(1280, 720,
                                "Dear ImGui GLFW+Vulkan example", nullptr, nullptr);

    if (!glfwVulkanSupported())
    {
        printf("GLFW: Vulkan Not Supported\n");
        throw std::runtime_error("GLFW: Vulkan Not Supported!");
    }
}

Window::~Window()
{
}

std::pair<const char **, uint32_t> Window::GetInstanceExtensions()
{
    uint32_t glfwExtensionCount;
    auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    return std::make_pair(glfwExtensions, glfwExtensionCount);
}
