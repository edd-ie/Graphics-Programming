//
// Created by _edd.ie_ on 22/01/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <string>

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "../Renderer/MainRenderer.h"
#include "../resource/Models/Model.h"

class Window {
    GLFWwindow *mainWindow = nullptr;
    std::unique_ptr<MainRenderer> mainRenderer;
    std::unique_ptr<Model> model;
public:
    bool init(unsigned int width, unsigned int height, const std::string& title);
    void mainLoop();
    void handleKeyEvents(int key, int scancode, int action, int mods);
    void handleMouseButtonEvents(int button, int action, int mods);
    void handleWindowCloseEvents();
    void cleanup();

};

#endif //WINDOW_H
