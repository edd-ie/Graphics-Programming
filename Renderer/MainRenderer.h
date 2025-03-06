//
// Created by _edd.ie_ on 07/02/2025.
//

#ifndef MainRENDERER_H
#define MainRENDERER_H

#pragma once

#include <vector>
 #include <string>

#include <glad/glad.h>
 #include <GLFW/glfw3.h>

 #include <glm/glm.hpp>


 #include "Framebuffer.h"
 #include "VertexBuffer.h"
 #include "Texture.h"
 #include "Shader.h"
 #include "MainRenderData.h"

class MainRenderer {
    Shader basicShader{};
    Framebuffer frameBuffer{};
    VertexBuffer vertexBuffer{};
    Texture texture{};
    int triangleCount = 0;
public:
    bool init(unsigned int width, unsigned int height);
    void setSize(unsigned int width, unsigned int height);
    void cleanup();
    void uploadData(OGLMesh vertexData);
    void draw();
};

#endif //MainRENDERER_H
