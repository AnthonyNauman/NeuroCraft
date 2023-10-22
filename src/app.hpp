#pragma once
#include <string>
#include <memory>

#include "ui/main_window.hpp"

namespace nc {

    class App
    {
    public:
        App();
        ~App() {}
        App(const App&) = delete;
        App(App&&) = delete;
        App& operator=(const App&) = delete;
        App& operator=(App&&) = delete;

        int exec();

    private:
        std::unique_ptr<MainWindow>     _mainWindow;
    };
}
