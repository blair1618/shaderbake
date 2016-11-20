cmake_minimum_required(VERSION 3.2)

project(shaderbake)

set(CMAKE_C_STANDARD 11)

include_directories(include stb)
add_library(shaderbake source/context.c source/options.c source/quad.c source/shader.c source/framebuffer.c source/image.c)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(shaderbake glfw ${OPENGL_LIBRARIES})

add_executable(shader2png source/main.c)

target_link_libraries(shader2png shaderbake)
