cmake_minimum_required(VERSION 3.26)
cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

project(application
        VERSION 1.0 
        DESCRIPTION ""
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

################################################ Dependencies
# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
# set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
# set(GLFW_DOCUMENT_INTERNALS OFF CACHE BOOL "" FORCE)
set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw)

# IMGUI
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui)
set(IMGUI_FILES
   ${IMGUI_DIR}/imgui.cpp
   ${IMGUI_DIR}/imgui_widgets.cpp
   ${IMGUI_DIR}/imgui_tables.cpp
   ${IMGUI_DIR}/imgui_draw.cpp
   ${IMGUI_DIR}/imgui_demo.cpp
   ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
   ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
   )

# VULKAN
if(WIN32)
        # find_library(VULKAN_LIB NAMES vulkan-1 vulkan PATHS ${VULKAN_SDK}/Lib)
elseif(APPLE)
        find_package(Vulkan)
endif()
message(STATUS ${Vulkan_LIBRARY})
set(VULKAN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/vulkan/1.3.243.0)

add_subdirectory(${GLFW_DIR})

################################################ Executable
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(FILES_SRC 
   ${SRC_DIR}/Application.cpp
   ${SRC_DIR}/Window.cpp
   ${SRC_DIR}/GuiRenderer.cpp
   ${SRC_DIR}/Renderer/RendererBase.cpp
   )

add_executable(app ${CMAKE_CURRENT_SOURCE_DIR}/apps/main.cpp ${FILES_SRC} ${IMGUI_FILES})

target_include_directories(app PRIVATE ${SRC_DIR})
target_include_directories(app PRIVATE ${GLFW_DIR}/include)
target_include_directories(app PRIVATE ${IMGUI_DIR})
target_include_directories(app PRIVATE ${IMGUI_DIR}/backends)
target_include_directories(app PRIVATE ${VULKAN_DIR}/macOS/include)

target_link_libraries(app PRIVATE glfw)
target_link_libraries(app PRIVATE ${Vulkan_LIBRARY})