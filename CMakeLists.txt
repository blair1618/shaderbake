cmake_minimum_required(VERSION 3.2)

project(shader_bakery)

set(CMAKE_C_STANDARD 11)

include_directories(include)
add_library(shader_bakery source/context.c source/options.c source/quad.c source/shader.c)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(shader_bakery glfw ${OPENGL_LIBRARIES})

add_executable(bake_shader source/main.c)

target_link_libraries(bake_shader shader_bakery)
