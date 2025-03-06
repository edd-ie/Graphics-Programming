//
// Created by _edd.ie_ on 17/02/2025.
//

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Framebuffer {
    unsigned int bufferWidth = 640;
    unsigned int bufferHeight = 480;
    GLuint buffer = 0;
    GLuint colourTexture = 0;
    GLuint depthBuffer = 0;
    bool checkComplete();

public:
    bool init(unsigned int width, unsigned int height);
    bool resize(unsigned int newWidth, unsigned int newHeight);
    void bind(); // Enable drawing to the frame buffers
    void unbind(); // Disable drawing to the frame buffers
    void drawToScreen();
    void cleanup();
};

#endif //FRAMEBUFFER_H
