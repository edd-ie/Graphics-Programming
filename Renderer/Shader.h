//
// Created by _edd.ie_ on 28/02/2025.
//

#ifndef SHADER_H
#define SHADER_H

#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Shader {
    GLuint mShaderProgram = 0;
    GLuint readShader(std::string shaderFileName, GLuint shaderType);

public:
    bool loadShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName);
    void use();
    void cleanup();

};
#endif //SHADER_H
