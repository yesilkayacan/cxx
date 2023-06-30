add_executable(app main.cpp)

target_link_libraries(app PRIVATE app_lib)
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)