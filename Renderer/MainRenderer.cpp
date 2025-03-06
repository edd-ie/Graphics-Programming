//
// Created by _edd.ie_ on 07/02/2025.
//

#include "MainRenderer.h"
#include "../Display/Logger.h"

bool MainRenderer::init(unsigned int width, unsigned int height) {
    Logger::log(1, "Initializing GLAD...\n");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::log(1, "%s error: failed OpenGL initialization\n", __FUNCTION__);
        return false;
    }
    Logger::log(1, "Checking OpenGL version...\n");
    if (!GLAD_GL_VERSION_3_0) {
        Logger::log(1, "%s error: disputes with OpenGL version\n", __FUNCTION__);
        return false;
    }

    Logger::log(1, "Initializing framebuffer...\n");
    if (!frameBuffer.init(width, height)) {
        Logger::log(1, "%s error: failed framebuffer initialization\n", __FUNCTION__);
        return false;
    }

    Logger::log(1, "Loading texture...\n");
    if (!texture.loadTexture("../resource/textures/crate.png")) {
        Logger::log(1, "%s error: failed texture loading\n", __FUNCTION__);
        return false;
    }

    Logger::log(1, "Initializing vertex buffer...\n");
    vertexBuffer.init();
    Logger::log(1, "Loading shaders...\n");
    if (!basicShader.loadShaders("../shaders/basic.vert", "../shaders/basic.frag")) {
        Logger::log(1, "%s error: failed shader loading\n", __FUNCTION__);
        return false;
    }

    Logger::log(1, "Initialization successful!\n");
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