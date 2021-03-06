cmake_minimum_required(VERSION 3.1)

project(shaderbake)

set(CMAKE_C_STANDARD 11)

include_directories(include
        dependencies/lodepng
        dependencies/glfw/include
        )

add_library(shaderbake
        source/context.c
        source/framebuffer.c
        source/image.c
        source/options.c
        source/quad.c
        source/shader.c
        )

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")
list(APPEND CMAKE_C_FLAGS -Wno-deprecated-declarations)
add_subdirectory(dependencies/glfw)

add_library(lodepng dependencies/lodepng/lodepng.c)

target_link_libraries(shaderbake glfw lodepng ${OPENGL_LIBRARIES})

add_executable(shader2png source/main.c)

target_link_libraries(shader2png shaderbake)
