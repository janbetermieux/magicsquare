cmake_minimum_required(VERSION 3.17)
project(magicsquare)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc)

add_executable(magicsquare src/magicsquare.cpp)
find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_library(GLEW_LIBRARY NAMES GLEW glew32 glew glew32s PATH_SUFFIXES lib64)
find_package(GLEW 2.0 REQUIRED)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
target_link_libraries(magicsquare glfw OpenGL::OpenGL GLEW::GLEW)