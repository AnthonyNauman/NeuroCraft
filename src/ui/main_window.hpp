#pragma once
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_opengl3_loader.h>
#include <imgui.h>

#include <memory>
#include <string>

#include "../camera/camera_controller.hpp"
#include "../graphics/frame_buffer.hpp"
#include "../graphics/mesh.hpp"
#include "../graphics/shader.hpp"
#include "../managers/render_manager.hpp"
#define GL_SILENCE_DEPRECATION

namespace nc {

    class MainWindow
    {
    public:
        MainWindow(size_t w = 600, size_t h = 480, const std::string wName = "")
          : _windowName(wName)
          , _width(w)
          , _height(h)
          , mRenderManager()
        {
        }

        MainWindow(const MainWindow&) = delete;
        MainWindow(MainWindow&&)      = delete;
        MainWindow& operator=(const MainWindow&) = delete;
        MainWindow& operator=(MainWindow&&) = delete;
        ~MainWindow() {}

        int  init();
        void update();
        void shutdown();
        bool shouldClose() { return glfwWindowShouldClose(_glWindow); }

    private:
        void _setGLSLVersion();

    private:
        managers::RenderManager           mRenderManager;
        std::shared_ptr<graphics::Shader> _shader1;
        std::shared_ptr<graphics::Mesh>   _mesh1;
        GLFWwindow*                       _glWindow;
        const char*                       _glslVersion;
        const std::string                 _windowName;
        size_t                            _width;
        size_t                            _height;

        std::shared_ptr<graphics::FrameBuffer>    _frameBuffer;
        std::shared_ptr<camera::CameraController> m_CameraController;
    };
}
