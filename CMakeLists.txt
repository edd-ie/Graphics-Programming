cmake_minimum_required(VERSION 3.30)
project(OpenGL)

include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e # refs/tags/1.0.1
)


FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glm)

set(CMAKE_CXX_STANDARD 26)

file(GLOB SOURCES
        imports/src/glad.c
        .h
        .cpp
)

add_executable(OpenGL main.cpp
        Display/Window.cpp Display/Window.h
        Display/Logger.h Display/Logger.cpp
        Renderer/MainRenderer.h
        Renderer/MainRenderer.cpp
        Renderer/MainRenderData.h
        Renderer/Framebuffer.h
        Renderer/Framebuffer.cpp
        Renderer/VertexBuffer.h
        Renderer/VertexBuffer.cpp
        Renderer/Texture.h
        Renderer/Texture.cpp
        Renderer/Shader.h
        Renderer/Shader.cpp
        resource/Models/Model.h
        resource/Models/Model.cpp
        ${SOURCES}
)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL glm::glm)
target_include_directories(${PROJECT_NAME} PUBLIC imports/include imports/src window tools opengl model)