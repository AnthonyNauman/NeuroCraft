#include "main_window.hpp"
#include "camera.hpp"
#include "glm/glm/ext/vector_float3.hpp"
#include "imgui.h"
#include "iostream"

#include "../utils.hpp"
#include "../logger.hpp"
#include "../libs/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include <filesystem>
#include <gl/gl.h>
#include <memory>
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
        //! @note Добавить флаг докинга
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(_glWindow, true);
        ImGui_ImplOpenGL3_Init(_glslVersion);


        const char vPath[] = "../res/m_vertex.glsl";
        const char fPath[] = "../res/m_frag.glsl";
        
        mRenderManager.init();
        _shader1 = std::make_shared<graphics::Shader>(vPath, fPath);
        _mesh1 = std::make_shared<graphics::Mesh>(&point[0], 3, 3);
        // _shader1 = new Shader(vPath, fPath);
        //
        // GLuint points_vbo = 0;
        // glGenBuffers(1, &points_vbo);
        // glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
        // GLuint colors_vbo = 0;
        // glGenBuffers(1, &colors_vbo);
        // glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
        //
        // glGenVertexArrays(1, &vao);
        // glBindVertexArray(vao);
        // 
        // glEnableVertexAttribArray(0);
        // glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        // glEnableVertexAttribArray(1);
        // glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        //
        // _createFrameBuffer();

        return 0; 
    }
    
    void MainWindow::update()
    {
        

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGuiIO& io = ImGui::GetIO();
        // ImGui::DockSpaceOverViewport();

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
        // glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        mRenderManager.setClearColor(0.f, 0.f, 0.f, 0.f);
        mRenderManager.clear();

        // ImGui::Begin("Scene");
        // const float w = ImGui::GetContentRegionAvail().x;
        // const float h = ImGui::GetContentRegionAvail().y;
        // _rescaleFrameBuffer(w, h);
        // glViewport(0, 0, w, h);

        // ImVec2 pos = ImGui::GetCursorScreenPos();
        // ImGui::GetWindowDrawList()->AddImage(reinterpret_cast<void*>(_textureId)
                                            // , ImVec2(pos.x, pos.y)
                                            // , ImVec2(pos.x + w, pos.y + h)
                                            // , ImVec2(0, 1) 
                                            // , ImVec2(1, 0));

        // ImGui::End();
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
        mRenderManager.flush();
        // _bindFrameBuffer();
        // _shader1->useProgram();
        // glBindVertexArray(vao);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0);

        // _unbindFrameBuffer();    


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
    
    void MainWindow::_createFrameBuffer()
    {
        glGenFramebuffers(1, &_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

        glGenTextures(1, &_textureId);
        glBindTexture(GL_TEXTURE_2D, _textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureId, 0);
        
        glGenRenderbuffers(1, &_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, _RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _RBO);
        
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
            NC_LOG_ERROR("[_createFrameBuffer] framebuffer is not complete!!!");
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        
    }



    void MainWindow::_bindFrameBuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
    }
    
    void MainWindow::_unbindFrameBuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }    

    void MainWindow::_rescaleFrameBuffer(const float width, const float height)
    {
        glBindTexture(GL_TEXTURE_2D, _textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureId, 0);
        
        glBindRenderbuffer(GL_RENDERBUFFER, _RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _RBO);
    }
}
