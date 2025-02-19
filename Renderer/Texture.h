//
// Created by _edd.ie_ on 19/02/2025.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture {
    GLuint mTexture = 0;
public:
    bool loadTexture(const std::string& textureFilename);
    void bind();
    void unbind();
    void cleanup();
};

#endif //TEXTURE_H
