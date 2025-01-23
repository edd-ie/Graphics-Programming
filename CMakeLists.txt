cmake_minimum_required(VERSION 3.30)
project(OpenGL)

set(CMAKE_CXX_STANDARD 26)

find_package(glfw3 CONFIG REQUIRED)


add_executable(OpenGL main.cpp
        Display/Window.cpp Display/Window.h
        Display/Logger.h Display/Logger.cpp)
target_link_libraries(OpenGL PRIVATE glfw)


