#pragma once
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

#include "../libs/nlohmann_json/include/nlohmann/json.hpp"
#include "ui/main_window.hpp"

using json = nlohmann::json;

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
        void                        initConfig();
        std::unique_ptr<MainWindow> m_mainWindow;
    };
}
