//
// Created by _edd.ie_ on 22/01/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW/glfw3.h>
class Window {
    GLFWwindow *mainWindow = nullptr;
public:
    bool init(unsigned int width, unsigned int height, const std::string& title);
    void mainLoop();
    void cleanup();

};

#endif //WINDOW_H
