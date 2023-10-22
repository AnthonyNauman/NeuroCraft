// #include <GLFW/glfw3.h>
#include <memory>
#include "app.hpp"


int main(void)
{
    auto app = std::make_unique<nc::App>();

    return app->exec();
}
