#pragma once
#include "vulkan/vulkan.h"

#include "Window.hpp"

class RendererBase
{
public:
    RendererBase(const Window &window);
    ~RendererBase();

protected:
    void CreateInstance();

    const Window &m_window;

    // Data
    // Instance
    VkInstance m_instance = VK_NULL_HANDLE;
    VkAllocationCallbacks *m_allocator = nullptr;
    VkDebugReportCallbackEXT m_debugReport = VK_NULL_HANDLE;

private:
    // VK Data
    // VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    // VkDevice m_logicalDevice = VK_NULL_HANDLE;

    // Data
    // // Instance
    // VkInstance m_Instance = VK_NULL_HANDLE;
    // VkAllocationCallbacks *m_allocator = nullptr;
    // VkDebugReportCallbackEXT m_debugReport = VK_NULL_HANDLE;

    // VkPhysicalDevice g_PhysicalDevice = VK_NULL_HANDLE;
    // VkDevice g_Device = VK_NULL_HANDLE;
    // uint32_t g_QueueFamily = (uint32_t)-1;
    // VkQueue g_Queue = VK_NULL_HANDLE;
    // VkPipelineCache g_PipelineCache = VK_NULL_HANDLE;
    // VkDescriptorPool g_DescriptorPool = VK_NULL_HANDLE;
};