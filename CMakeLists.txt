cmake_minimum_required(VERSION 3.26)
cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

project(application
        VERSION 1.0 
        DESCRIPTION ""
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
# set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
# set(GLFW_DOCUMENT_INTERNALS OFF CACHE BOOL "" FORCE)
set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw)

# IMGUI
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui)

# VULKAN
if(WIN32)
# find_library(VULKAN_LIB NAMES vulkan-1 vulkan PATHS ${VULKAN_SDK}/Lib)
elseif(APPLE)
find_package(Vulkan)
endif()
message(STATUS ${Vulkan_LIBRARY})
set(VULKAN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/vulkan/1.3.243.0)

add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(${GLFW_DIR})