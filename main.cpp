#include <memory>
#include "Display/Window.h"
#include "Display/Logger.h"


int main(int argc, char *argv[]) {
    std::unique_ptr<Window> w = std::make_unique<Window>();

    if (!w->init(640, 480, "Yggdrasil")) {
        Logger::log(1, "%s error: Window init error\n", __FUNCTION__);
        return -1;
    }

    w->mainLoop();
    w->cleanup();
    return 0;
}