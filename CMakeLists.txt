cmake_minimum_required(VERSION 3.30)
project(OpenGL)

include(FetchContent)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.4)
FetchContent_MakeAvailable(glfw)


set(CMAKE_CXX_STANDARD 26)

add_executable(OpenGL main.cpp
        Display/Window.cpp Display/Window.h
        Display/Logger.h Display/Logger.cpp)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)
