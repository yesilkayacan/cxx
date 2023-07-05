#pragma once
#include "vulkan/vulkan.h"
#include "vulkan/vk_enum_string_helper.h"

// std
#include <stdexcept>
#include <string>

class Core
{
public:
    static void VkCheck(VkResult result)
    {
        if (result == VK_SUCCESS)
            return;

        const char *resultString = string_VkResult(result);
        throw std::runtime_error("Vulkan error: " + std::string(resultString));
    }
};