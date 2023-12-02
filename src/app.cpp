#include "app.hpp"
#include "logger.hpp"

namespace nc {

    App::App() { NC_LOG_INFO("App created"); }

    int App::exec()
    {
        std::string projName = std::string(PROJECT_NAME) + "_" + std::string(PROJECT_VERSION);
        _mainWindow          = std::make_unique<MainWindow>(1600, 800, projName);
        int errorCode        = _mainWindow->init();
        if (errorCode) {
            NC_LOG_ERROR("Cant init main window!");
            return -1;
        }

        // Main loop
        while (!_mainWindow->shouldClose()) {
            _mainWindow->update();
        }
        // Cleanup
        _mainWindow->shutdown();
        return 0;
    }

}
