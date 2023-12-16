#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../camera/camera_controller.hpp"
#include "../graphics/frame_buffer.hpp"
#include "../graphics/mesh.hpp"
#include "../graphics/shader.hpp"
#include "../managers/render_manager.hpp"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_opengl3_loader.h>
#include <imgui.h>
#include <stdint.h>

#include <GLFW/glfw3.h>
#define GL_SILENCE_DEPRECATION

namespace nc {

    class MainWindow
    {
    public:
        MainWindow(size_t w = 600, size_t h = 480, const std::string wName = "")
          : m_windowName(wName)
          , m_width(w)
          , m_height(h)
          , m_renderManager()
        {}

        MainWindow(const MainWindow&) = delete;
        MainWindow(MainWindow&&)      = delete;
        MainWindow& operator=(const MainWindow&) = delete;
        MainWindow& operator=(MainWindow&&) = delete;
        ~MainWindow() {}

        int  init();
        void update();
        void shutdown();
        bool shouldClose() { return glfwWindowShouldClose(m_glWindow); }

    private:
        void _setGLSLVersion();

    private:
        managers::RenderManager           m_renderManager;
        std::shared_ptr<graphics::Shader> m_shader1;
        std::shared_ptr<graphics::Mesh>   m_mesh1;
        GLFWwindow*                       m_glWindow;
        const char*                       m_glslVersion;
        const std::string                 m_windowName;
        size_t                            m_width;
        size_t                            m_height;

        std::shared_ptr<graphics::FrameBuffer>    m_frameBuffer;
        std::shared_ptr<camera::CameraController> m_CameraController;
    };
}
