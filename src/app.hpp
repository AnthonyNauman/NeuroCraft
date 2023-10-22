#pragma once
#include <string>
#include <memory>
#include <GLFW/glfw3.h> 
#define GL_SILENCE_DEPRECATION

namespace nc {

    class App
    {
    public:
        App();
        ~App();
        App(const App&) = delete;
        App(App&&) = delete;
        App& operator=(const App&) = delete;
        App& operator=(App&&) = delete;

        int exec();
        void update();


    private:
    };
}
