# Add source files in the src directory
set(IMGUI_FILES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
)

file(GLOB FILES_SRC CONFIGURE_DEPENDS "*.cpp")

add_library(app_lib STATIC ${FILES_SRC} ${IMGUI_FILES})
target_compile_features(app_lib PUBLIC cxx_std_17)

target_include_directories(app_lib PRIVATE ${GLFW_DIR}/include)
target_include_directories(app_lib PRIVATE ${IMGUI_DIR})
target_include_directories(app_lib PRIVATE ${IMGUI_DIR}/backends)
target_include_directories(app_lib PRIVATE ${VULKAN_DIR}/macOS/include)

target_link_libraries(app_lib PRIVATE glfw ${Vulkan_LIBRARY})