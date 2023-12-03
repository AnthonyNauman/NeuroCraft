#include "app.hpp"
#include "logger.hpp"

namespace nc {

    App::App() { NC_LOG_INFO("App created"); }

    int App::exec()
    {
        std::string projName = std::string(PROJECT_NAME) + "_" + std::string(PROJECT_VERSION);
        m_mainWindow         = std::make_unique<MainWindow>(1600, 800, projName);
        int errorCode        = m_mainWindow->init();
        if (errorCode) {
            NC_LOG_ERROR("Cant init main window!");
            return -1;
        }

        initConfig();

        // Main loop
        while (!m_mainWindow->shouldClose()) {
            m_mainWindow->update();
        }
        // Cleanup
        m_mainWindow->shutdown();
        return 0;
    }

    void App::initConfig()
    {
        std::string configPath = "config";
        if (!std::filesystem::exists(std::filesystem::path(configPath))) {
            std::ofstream config;

            json configJsonFile;
            configJsonFile["log"] = { { "VisibleCategories", { "" } }, { "LogLevel", 0 } };

            config.open(configPath);
            if (config.is_open()) {
                config << configJsonFile.dump();
                config.flush();
                config.close();
            }
        } else {
            std::ifstream configFile(configPath);
            json          configJsonFile;
            try {
                configJsonFile = json::parse(configFile);
            } catch (...) {
                std::ofstream bufferConfigFile;
                bufferConfigFile.open(configPath);
                if (bufferConfigFile.is_open()) {
                    bufferConfigFile << "";
                    json bufferConfigJsonFile;
                    bufferConfigJsonFile["log"] = { { "VisibleCategories", { "" } }, { "LogLevel", 0 } };
                    bufferConfigFile << bufferConfigJsonFile.dump();
                    bufferConfigFile.flush();
                    bufferConfigFile.close();
                    return;
                }
            }
            auto logger = nc::Logger::getInstance();

            if (configJsonFile.contains("log")) {
                if (configJsonFile["log"].contains("VisibleCategories")) {
                    for (auto category : configJsonFile["log"]["VisibleCategories"]) {
                        logger->addVisibleCategories(static_cast<std::string>(category));
                    }
                }
                if (configJsonFile["log"].contains("LogLevel")) {
                    logger->setLogLevel(static_cast<int>(configJsonFile["log"]["LogLevel"]));
                }
            }
        }
    }
}
