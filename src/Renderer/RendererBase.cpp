#include "RendererBase.hpp"
#include "Base.hpp"
#include "Core.hpp"

// std
#include <vector>
#include <utility>

static bool IsExtensionAvailable(const std::vector<VkExtensionProperties> &properties, const char *extension)
{
    for (const VkExtensionProperties &p : properties)
        if (strcmp(p.extensionName, extension) == 0)
            return true;
    return false;
}

#ifdef VULKAN_DEBUG_REPORT
static VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char *pLayerPrefix, const char *pMessage, void *pUserData)
{
    (void)flags;
    (void)object;
    (void)location;
    (void)messageCode;
    (void)pUserData;
    (void)pLayerPrefix; // Unused arguments
    fprintf(stderr, "[vulkan] Debug report from ObjectType: %i\nMessage: %s\n\n", objectType, pMessage);
    return VK_FALSE;
}
#endif // IMGUI_VULKAN_DEBUG_REPORT

RendererBase::RendererBase(const Window &window)
    : m_window(window)
{
}

RendererBase::~RendererBase()
{
}

void RendererBase::CreateInstance()
{
    VkResult err;

    // Create Vulkan Instance
    {

        // VkApplicationInfo appInfo{};
        // appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        // appInfo.pApplicationName = "Hello Triangle";
        // appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        // appInfo.pEngineName = "No Engine";
        // appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        // appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        // createInfo.pApplicationInfo = &appInfo;

        // Enumerate available extensions
        uint32_t propertiesCount;
        std::vector<VkExtensionProperties> properties;
        vkEnumerateInstanceExtensionProperties(nullptr, &propertiesCount, nullptr);
        properties.resize(propertiesCount);
        err = vkEnumerateInstanceExtensionProperties(nullptr, &propertiesCount, properties.data());
        Core::VkCheck(err);

        // Manage required extensions
        // auto std::pair<const char **, uint32_t> &extensions = Window::GetInstanceExtensions();
        auto [glfwExtensions, extensionsCount] = Window::GetInstanceExtensions();
        std::vector<const char *> extensions;
        for (uint32_t i = 0; i < extensionsCount; i++)
            extensions.push_back(glfwExtensions[i]);

        if (IsExtensionAvailable(properties, VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME))
            extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
#ifdef VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
        if (IsExtensionAvailable(properties, VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME))
        {
            extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
            createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        }
#endif

        // Enabling validation layers
#ifdef VULKAN_DEBUG_REPORT
        const char *layers[] = {"VK_LAYER_KHRONOS_validation"};
        createInfo.enabledLayerCount = 1;
        createInfo.ppEnabledLayerNames = layers;
        extensions.push_back("VK_EXT_debug_report");
#endif

        // Create Vulkan Instance
        createInfo.enabledExtensionCount = (uint32_t)extensions.size();
        createInfo.ppEnabledExtensionNames = extensions.data();
        err = vkCreateInstance(&createInfo, m_allocator, &m_instance);
        Core::VkCheck(err);

        // Setup the debug report callback
#ifdef VULKAN_DEBUG_REPORT
        auto vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(m_instance, "vkCreateDebugReportCallbackEXT");
        assert(vkCreateDebugReportCallbackEXT != nullptr);
        VkDebugReportCallbackCreateInfoEXT debug_report_ci = {};
        debug_report_ci.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        debug_report_ci.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
        debug_report_ci.pfnCallback = debug_report;
        debug_report_ci.pUserData = nullptr;
        err = vkCreateDebugReportCallbackEXT(m_instance, &debug_report_ci, m_allocator, &m_debugReport);
        Core::VkCheck(err);
#endif
    }
}