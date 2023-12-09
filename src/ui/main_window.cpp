#include "main_window.hpp"
#include "../camera/camera.hpp"
#include "glm/glm/ext/vector_float3.hpp"
#include "imgui.h"
#include "iostream"

#include "../libs/glad/include/glad/glad.h"
#include "../logger/logger.hpp"
#include "../utils.hpp"
#include "GLFW/glfw3.h"
#include <algorithm>
#include <filesystem>
#include <gl/gl.h>

namespace nc {

    // clang-format off
    GLfloat point[] = {
        0.0f,   0.5f,   0.0f,
        0.2f,   -0.2f,  0.0f,
        -0.5f,  -0.5f,  0.0f
    }; 
    GLfloat color[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f
    };

    float squareVertices[]
    {
         0.5f,   0.5f,  0.0f,
         0.5f,  -0.5f,  0.0f,
        -0.5f,  -0.5f,  0.0f,
        -0.5f,   0.5f,  0.0f
    };

    uint32_t squareElements[]
    {
        0, 3, 1,
        1, 3, 2
    };
    // float vertices[] = {
    //     // positions         // colors
    //      0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    //     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
    //      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    // };

    // clang-format on
    float camPos[]           = { 0.f, 0.f, 1.f };
    float camRot[]           = { 0.f, 0.f, 0.f };
    bool  bPerspectiveCamera = false;

    GLuint vao;

    int MainWindow::init()
    {
        if (!glfwInit())
            return -1;

        _setGLSLVersion();
        glfwSetErrorCallback(utils::glfw_error_callback);
        /* Create a windowed mode window and its OpenGL context */
        m_glWindow = glfwCreateWindow(m_width, m_height, m_windowName.c_str(), nullptr, nullptr);
        if (!m_glWindow) {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(m_glWindow);
        // Create window with graphics context
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            NC_LOG("MainWindow", LogLevels::ERR) << "Can't init Glad";
        }
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(m_glWindow, true);
        ImGui_ImplOpenGL3_Init(m_glslVersion);

        const char vPath[] = "../res/m_vertex.glsl";
        const char fPath[] = "../res/m_frag.glsl";

        m_renderManager.init();
        m_CameraController = std::make_shared<camera::CameraController>();
        m_frameBuffer      = std::make_shared<graphics::FrameBuffer>(m_width, m_height);
        m_shader1          = std::make_shared<graphics::Shader>(vPath, fPath);
        m_mesh1            = std::make_shared<graphics::Mesh>(&squareVertices[0], 4, 3, &squareElements[0], 6);

        return 0;
    }

    void MainWindow::update()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiIO& io = ImGui::GetIO();
        ImGui::DockSpaceOverViewport();

        //! @todo MyStaff
        ImGui::Begin("test");
        ImGui::SliderFloat3("Camera position", camPos, -10.f, 10.f);
        ImGui::SliderFloat3("Camera rotation", camRot, 0.f, 360.f);
        ImGui::Checkbox("Perspective", &bPerspectiveCamera);

        m_CameraController->setCameraPos(glm::vec3(camPos[0], camPos[1], camPos[2]));
        m_CameraController->setCameraPos(glm::vec3(camRot[0], camRot[1], camRot[2]));

        ImGui::End();

        double cursorX;
        double cursorY;
        glfwGetCursorPos(m_glWindow, &cursorX, &cursorY);
        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents();

        m_frameBuffer->setColor(0.1f, 0.2f, 0.4f, 1.f);
        m_renderManager.submit(std::move(std::make_unique<graphics::renderCommands::PushFrameBuffer>(m_renderManager, m_frameBuffer)));

        if (ImGui::Begin("Scene")) {
            ImVec2      scenePos = ImGui::GetCursorScreenPos();
            const float sWidth   = ImGui::GetContentRegionAvail().x;
            const float sHeight  = ImGui::GetContentRegionAvail().y;

            ImVec2 mPos = ImGui::GetMousePos();
            // if mouse in scene we can get input from it
            // clang-format off
            bool bMouseOnScene = mPos.x > scenePos.x && mPos.x < scenePos.x + sWidth &&
                                 mPos.y > scenePos.y && mPos.y < scenePos.y + sHeight;
            // clang-format on

            ImVec2 sMousePos = { mPos.x - scenePos.x, mPos.y - scenePos.y };
            if (bMouseOnScene) 
            {
                //!\todo убрать потом "Пример нового логирования"
                NC_LOG(consts::logCategory::APP, LogLevels::DEBUG)<<"dvigaetso";
             
                // LogStream ls ("lskjdf", LogLevels::INFO);
                // ls  << "krodetso" << "bistro" << "mimo";
                // NC_LOG("Sample", LogLevels::CRITICAL)<<("polzaet");
                // NC_LOG("Sample2", LogLevels::CRITICAL)<<("polzaet2");
            }
            ImVec2 endPos = { scenePos.x + sWidth, scenePos.y + sHeight };
            ImVec2 uv0    = { 0, 1 };
            ImVec2 uv1    = { 1, 0 };
            ImGui::GetWindowDrawList()->AddImage(reinterpret_cast<void*>(m_frameBuffer->textureId()), scenePos, endPos, uv0, uv1);
        }
        ImGui::End();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backupContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupContext);
        }

        m_shader1->setUniformMat4fv("translate", m_CameraController->cameraViewMatrix());
        auto rc = std::make_unique<graphics::renderCommands::RenderMesh>(m_mesh1, m_shader1);
        m_renderManager.submit(std::move(rc));
        m_renderManager.submit(std::move(std::move(std::make_unique<graphics::renderCommands::PopFrameBuffer>(m_renderManager))));
        m_renderManager.flush();

        glfwSwapBuffers(m_glWindow);
    }

    void MainWindow::shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        m_renderManager.shutdown();
        glfwDestroyWindow(m_glWindow);
        glfwTerminate();
    }

    void MainWindow::_setGLSLVersion()
    {
#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        _glslVersion = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#else
        // GL 3.0 + GLSL 130
        m_glslVersion = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
    }
}
