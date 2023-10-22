#include "app.hpp"
#include "logger.hpp"


namespace nc {

    App::App()
    {
        __logInfo("App created");
    }
    
    int App::exec()
    {

        _mainWindow = std::make_unique<MainWindow>();
        std::string projName = std::string(PROJECT_NAME) + "_" + std::string(PROJECT_VERSION);
        _mainWindow.reset(new MainWindow(1600, 800, projName));
        int errorCode = _mainWindow->init();
        if(errorCode) {
            __logCritical("Cant init main window!");
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
