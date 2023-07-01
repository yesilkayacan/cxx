cmake_minimum_required(VERSION 3.26)
cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

project(application
        VERSION 1.0 
        DESCRIPTION ""
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw)