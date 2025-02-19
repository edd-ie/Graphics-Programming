//
// Created by _edd.ie_ on 18/02/2025.
//

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MainRenderData.h"

class VertexBuffer {
    GLuint vertexArray = 0;
    GLuint vertexBuffer = 0;
public:
    void init();
    void uploadData(OGLMesh vertexData);
    void bind();
    void unbind();
    void draw(GLuint mode, unsigned int start,
    unsigned int num);
    void cleanup();
};

#endif //VERTEXBUFFER_H
