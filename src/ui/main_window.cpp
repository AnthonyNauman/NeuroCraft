#include "main_window.hpp"
#include "camera.hpp"
#include "glm/glm/ext/vector_float3.hpp"
#include "imgui.h"
#include "iostream"

#include "../utils.hpp"
#include "../logger.hpp"
#include "../libs/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include <algorithm>
#include <filesystem>
#include <gl/gl.h>
#include <memory>
#include <stdint.h>
#include <vector>

namespace nc {

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
    float camPos[] = {0.f, 0.f, 1.f};
    float camRot[] = {0.f, 0.f, 0.f};
    bool bPerspectiveCamera = false;

    GLuint vao;



    int MainWindow::init()
    {
        if (!glfwInit())
            return -1;
        
        _setGLSLVersion();
        glfwSetErrorCallback(utils::glfw_error_callback);
        /* Create a windowed mode window and its OpenGL context */
        _glWindow = glfwCreateWindow(_width, _height, _windowName.c_str(), nullptr, nullptr);
        if (!_glWindow )
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(_glWindow );
        // Create window with graphics context
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            NC_LOG_CRIT("Can't init Glad"); 
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
        ImGui_ImplGlfw_InitForOpenGL(_glWindow, true);
        ImGui_ImplOpenGL3_Init(_glslVersion);


        const char vPath[] = "../res/m_vertex.glsl";
        const char fPath[] = "../res/m_frag.glsl";
        
        mRenderManager.init();
        _frameBuffer = std::make_shared<graphics::FrameBuffer>(_width, _height);
        _shader1 = std::make_shared<graphics::Shader>(vPath, fPath);
        _mesh1 = std::make_shared<graphics::Mesh>(&squareVertices[0], 4, 3, &squareElements[0], 6);

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
        
        _camera.setPosition(glm::vec3(camPos[0], camPos[1], camPos[2]));
        _camera.setRotation(glm::vec3(camRot[0],camRot[1],camRot[2]));
        _camera.setProjectionMode(bPerspectiveCamera ? Camera::Projection::Perspective : Camera::Projection::Orthographic);

        ImGui::End();


        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents() ;
        
        _frameBuffer->setColor(0.1f, 0.2f, 0.4f, 1.f);
        mRenderManager.submit(std::move(std::make_unique<graphics::renderCommands::PushFrameBuffer>(mRenderManager, _frameBuffer)));
        
        if(ImGui::Begin("Scene")) {
            
            const float w = ImGui::GetContentRegionAvail().x;
            const float h = ImGui::GetContentRegionAvail().y;
            ImVec2 startPos = ImGui::GetCursorScreenPos();
            ImVec2 endPos = {startPos.x + w, startPos.y + h};
            ImVec2 uv0 = {0, 1};
            ImVec2 uv1 = {1, 0};
            ImGui::GetWindowDrawList()->AddImage(reinterpret_cast<void*>(_frameBuffer->textureId())
                                                , startPos 
                                                , endPos
                                                , uv0
                                                , uv1);

        }
        ImGui::End();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if(ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backupContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupContext);
        }

        _shader1->setUniformMat4fv("translate", _camera.camViewMatrix());
        auto rc = std::make_unique<graphics::renderCommands::RenderMesh>(_mesh1, _shader1);
        mRenderManager.submit(std::move(rc));
        mRenderManager.submit(std::move(std::move(std::make_unique<graphics::renderCommands::PopFrameBuffer>(mRenderManager))));
        mRenderManager.flush();

        glfwSwapBuffers(_glWindow);
    }
    
    void MainWindow::shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        mRenderManager.shutdown();
        glfwDestroyWindow(_glWindow);
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
        _glslVersion = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
    }
}
