cmake_minimum_required(VERSION 3.20)
project(glad)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fPIC" )
add_library(glad include/glad/glad.h include/KHR/khrplatform.h src/glad.c)
target_include_directories(glad PUBLIC include/)
