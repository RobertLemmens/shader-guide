cmake_minimum_required(VERSION 3.21)
project(shader_guide C)

set(CMAKE_C_STANDARD 11)

add_subdirectory("${PROJECT_SOURCE_DIR}/libraries/glad")
add_subdirectory("${PROJECT_SOURCE_DIR}/libraries/glfw")
add_subdirectory("${PROJECT_SOURCE_DIR}/libraries/cglm")

include_directories(${CMAKE_SOURCE_DIR}/libraries/glad/include
        ${CMAKE_SOURCE_DIR}/libraries/cglm/include
        ${CMAKE_SOURCE_DIR}/libraries/glfw/include)

add_executable(shader_guide src/shader_guide.c src/shg_ogl_wrapper.c src/shg_ogl_wrapper.h src/shg_utils.h src/shg_utils.c src/shg_camera.c src/shg_camera.h)

target_link_libraries(shader_guide glad glfw cglm)