#include "app.hpp"
#include "logger.hpp"

namespace nc {

    App::App() { NC_LOG_INFO("App created"); }

    int App::exec()
    {
        std::string projName = std::string(PROJECT_NAME) + "_" + std::string(PROJECT_VERSION);
        m_mainWindow          = std::make_unique<MainWindow>(1600, 800, projName);
        int errorCode        = m_mainWindow->init();
        if (errorCode) {
            NC_LOG_ERROR("Cant init main window!");
            return -1;
        }

        // Main loop
        while (!m_mainWindow->shouldClose()) {
            m_mainWindow->update();
        }
        // Cleanup
        m_mainWindow->shutdown();
        return 0;
    }

}
