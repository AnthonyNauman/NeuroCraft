#pragma once
#include <string>


#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include <GLFW/glfw3.h> 
#define GL_SILENCE_DEPRECATION


namespace nc {

    class MainWindow
    {
    public:
        MainWindow(size_t w = 600, size_t h = 480, const std::string wName = "" ) 
            :_windowName(wName)
            ,_width(w)
            ,_height(h)
            {}
        
        MainWindow(const MainWindow&) = delete;
        MainWindow(MainWindow&&) = delete;
        MainWindow& operator=(const MainWindow&) = delete;
        MainWindow& operator=(MainWindow&&) = delete;
        ~MainWindow() {} 

        int init();
        void update();
        void shutdown();
        bool shouldClose() {return glfwWindowShouldClose(_glWindow);}
    private:
        void _setGLSLVersion();

    private:
        GLFWwindow*         _glWindow;
        const char*         _glslVersion;
        const std::string   _windowName;
        size_t              _width; 
        size_t              _height; 
    };
}