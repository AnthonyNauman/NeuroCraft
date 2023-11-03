#include "app.hpp"

int main(void)
{
    auto app = nc::App::getInstance();

    return app->exec();
}
