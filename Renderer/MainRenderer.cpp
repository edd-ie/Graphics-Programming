//
// Created by _edd.ie_ on 07/02/2025.
//

#include "MainRenderer.h"

bool MainRenderer::init(unsigned int width, unsigned int height) {
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))){
        return false;
    }
    if (!GLAD_GL_VERSION_4_6) {
        return false;
    }

    if (!frameBuffer.init(width, height)) {
        return false;
    }
    if (!texture.loadTexture( "textures/crate.png")) {
        return false;
    }

    vertexBuffer.init();
    if (!basicShader.loadShaders( "shader/basic.vert", "shaders/basic.frag")) {
        return false;
    }
    return true;
}

void MainRenderer::setSize(unsigned int width, unsigned int height) {
    frameBuffer.resize(width, height);
    glViewport(0, 0, width, height);
}

void MainRenderer::uploadData(OGLMesh vertexData) {
    triangleCount = vertexData.vertices.size();
    vertexBuffer.uploadData(vertexData);
}

void MainRenderer::draw() {
    frameBuffer.bind();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);  //Back-face culling.

    basicShader.use();    // load the shader program, enables processing of the vertex data
    texture.bind();       // Bind the texture to draw textured triangles
    vertexBuffer.bind();  // Bind the vertex array, to have the triangle data available

    // Send vertex data to the GPU to be processed by the shaders.
    vertexBuffer.draw(GL_TRIANGLES, 0, triangleCount);
    vertexBuffer.unbind();
    texture.unbind();

    // Draw the content of the framebuffer to the screen
    frameBuffer.drawToScreen();
}

void MainRenderer::cleanup() {
    basicShader.cleanup();
    texture.cleanup();
    vertexBuffer.cleanup();
    frameBuffer.cleanup();
}