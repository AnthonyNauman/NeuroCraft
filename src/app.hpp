#pragma once
#include <memory>
#include <string>

#include "ui/main_window.hpp"

namespace nc {

    class App
    {
    private:
        App();

    public:
        static std::shared_ptr<App> getInstance()
        {
            static std::shared_ptr<App> appPtr{ new App() };
            return appPtr;
        }
        ~App() {}

        int exec();

        App(App&&)      = delete;
        App(const App&) = delete;
        App& operator=(const App&) = delete;
        App& operator=(App&&) = delete;

    private:
        std::unique_ptr<MainWindow> _mainWindow;
    };
}
