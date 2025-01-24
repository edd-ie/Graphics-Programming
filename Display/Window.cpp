//
// Created by _edd.ie_ on 22/01/2025.
//
#include "Window.h"
#include "Logger.h"

bool Window::init(const unsigned int width, const unsigned int height, const std::string& title) {
    if (!glfwInit()) {
        Logger::log(1, "%s: glfwInit() error\n", __FUNCTION__);
        return false;
    }

    /* set a "hint" for the NEXT window created*/
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    mainWindow = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height),
    title.c_str(), nullptr, nullptr);


    if (!mainWindow) {
        Logger::log(1, "%s: Could not create window\n", __FUNCTION__);
        glfwTerminate();
        return false;
    }

    // Adding OpenGL context to the window
    glfwMakeContextCurrent(mainWindow);

    Logger::log(1, "%s: Window successfully initialized\n", __FUNCTION__);
    return true;
}

void Window::mainLoop() {
    // Enable vertical sync to prevent tearing & flickering
    glfwSwapInterval(1);

    // Background colour
    float colour = 0.0f;

    while (!glfwWindowShouldClose(mainWindow)) {

        colour >= 1.0f ? colour = 0.0f : colour += 0.01f;
        glClearColor(colour, colour, colour, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        glfwSwapBuffers(mainWindow);

        /* poll events in a loop */
        glfwPollEvents();


    }
}

void Window::cleanup() {
    Logger::log(1, "%s: Terminating Window\n", __FUNCTION__);
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}