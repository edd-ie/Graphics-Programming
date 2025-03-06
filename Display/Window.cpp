//
// Created by _edd.ie_ on 22/01/2025.
//
#include "Window.h"
#include "Logger.h"
void glfwErrorCallback(int error, const char* description) {
    Logger::log(1, "GLFW Error (%d): %s\n", error, description);
}


bool Window::init(const unsigned int width, const unsigned int height, const std::string& title) {
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit()) {
        Logger::log(1, "%s: glfwInit() error\n", __FUNCTION__);
        return false;
    }


    /* set a "hint" for the NEXT window
     * create an OpenGL 4.6 window with the core profile set
     */
    Logger::log(1, "Setting GLFW window hints...\n");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// forward compatible with newer versions of OpenGL as they become available but not backward compatible (it will not run on devices that do not support OpenGL 3.3

    // Creating a window
    Logger::log(1, "Creating GLFW window...\n");
    mainWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!mainWindow) {
        Logger::log(1, "%s: Could not create window\n", __FUNCTION__);
        glfwTerminate();
        return false;
    }

    Logger::log(1, "Making OpenGL context current...\n");
    glfwMakeContextCurrent(mainWindow);


    //Creating the renderer object with the folder of the executable file
    mainRenderer = std::make_unique<MainRenderer>();
    if (!mainRenderer->init(width, height)) {
        Logger::log(1, "%s: Could not create renderer\n", __FUNCTION__);
        glfwTerminate();
        return false;
    }

    // Adding OpenGL context to the window
    //glfwMakeContextCurrent(mainWindow);
    //glfwSetWindowUserPointer(mainWindow, this);

    //Making window resizeable, setSize()- will resize the OpenGL viewport and framebuffer
    Logger::log(1, "Setting GLFW window user pointer...\n");
    glfwSetWindowUserPointer(mainWindow, mainRenderer.get());
    glfwSetWindowSizeCallback(mainWindow, [](GLFWwindow *win, int width, int height) {
        auto renderer = static_cast<MainRenderer*>(glfwGetWindowUserPointer(win));
        renderer->setSize(width, height);
    });

    //Initializing the model
    Logger::log(1, "Initializing Model object...\n");
    model = std::make_unique<Model>();
    model->init();

    //Callback for key events
    Logger::log(1, "Setting GLFW key callback...\n");
    glfwSetKeyCallback(mainWindow, [](GLFWwindow *win, int key,
        int scancode, int action, int mods) {
        auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        thisWindow->handleKeyEvents(key, scancode, action, mods);
    });

    //Callback for mouse events
    Logger::log(1, "Setting GLFW mouse button callback...\n");
    glfwSetMouseButtonCallback(mainWindow, [](GLFWwindow *win, int button, int action, int mods) {
        auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        thisWindow->handleMouseButtonEvents(button, action,
        mods);
    });

    //On window close event
    Logger::log(1, "Setting GLFW window close callback...\n");
    glfwSetWindowCloseCallback(mainWindow, [](GLFWwindow *win) {
        auto thisWindow = static_cast<Window*>(
        glfwGetWindowUserPointer(win));
        thisWindow->handleWindowCloseEvents();
    });

    Logger::log(1, "%s: Window successfully initialized\n", __FUNCTION__);
    return true;
}


void Window::mainLoop() {
    // Enable vertical sync to prevent tearing & flickering
    glfwSwapInterval(1);

    // Get vertex and texture data from the model and feed the renderer
    mainRenderer->uploadData(model->getVertexData());

    // Background colour
    //float colour = 0.0f;

    while (!glfwWindowShouldClose(mainWindow)) {

        /*// Make a grey background
        colour >= 1.0f ? colour = 0.0f : colour += 0.01f;
        glClearColor(colour, colour, colour, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);*/

        // Draws the vertex data of the model to the back buffer
        mainRenderer->draw();

        // Swap buffers
        glfwSwapBuffers(mainWindow);

        /* poll events in a loop */
        glfwPollEvents();


    }
}

void Window::handleKeyEvents(int key, int scancode, int action, int mods) {
    std::string actionName;
    switch (action) {
        case GLFW_PRESS:
            actionName = "pressed";
        break;
        case GLFW_RELEASE:
            actionName = "released";
        break;
        case GLFW_REPEAT:
            actionName = "repeated";
        break;
        default:
            actionName = "invalid";
        break;
    }
    const char *keyName = glfwGetKeyName(key, 0);
    Logger::log(1, "%s: key %s (key %i, scancode %i) %s\n", __FUNCTION__,
        keyName, key, scancode, actionName.c_str());
}

void Window::handleMouseButtonEvents(int button, int action, int mods) {
    std::string actionName;
    switch (action) {
        case GLFW_PRESS:
        actionName = "pressed";
        break;
        case GLFW_RELEASE:
        actionName = "released";
        break;
        default:
        actionName = "invalid";
        break;
    }

    std::string mouseButtonName;
    switch(button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            mouseButtonName = "left";
        break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            mouseButtonName = "middle";
        break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            mouseButtonName = "right";
        break;
        default:
            mouseButtonName = "other";
        break;
    }

    Logger::log(1, "%s: %s mouse button (%i) %s\n", __FUNCTION__,
        mouseButtonName.c_str(), button, actionName.c_str());
}

void Window::handleWindowCloseEvents() {
    Logger::log(1, "%s: Window got close event... bye!\n", __FUNCTION__);
}

void Window::cleanup() {
    Logger::log(1, "%s: Terminating Window\n", __FUNCTION__);
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}