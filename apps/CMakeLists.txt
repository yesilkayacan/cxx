file(GLOB IMGUI_FILES ${IMGUI_DIR}/*cpp ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp)

add_executable(app main_example.cpp ${IMGUI_FILES})

target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_include_directories(app PRIVATE ${GLFW_DIR}/include)
target_include_directories(app PRIVATE ${IMGUI_DIR}/)
target_include_directories(app PRIVATE ${IMGUI_DIR}/backends)
target_include_directories(app PRIVATE ${VULKAN_DIR}/macOS/include)

target_link_libraries(app PRIVATE app_lib)
target_link_libraries(app PRIVATE glfw)
target_link_libraries(app PRIVATE ${Vulkan_LIBRARY})