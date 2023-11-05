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
#include <memory>
#include <vector>

namespace nc {

    GLfloat point[] = {
        0.0f,   0.5f,   0.0f,
        0.8f,   -0.3f,  0.0f,
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

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(_glWindow, true);
        ImGui_ImplOpenGL3_Init(_glslVersion);


        const char vPath[] = "../res/m_vertex.glsl";
        const char fPath[] = "../res/m_frag.glsl";
        _shader1 = new Shader(vPath, fPath);

        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        return 0; 
    }
    
    void MainWindow::update()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        _shader1->useProgram();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        


        //! @todo MyStaff
        ImGui::Begin("test");
        ImGui::SliderFloat3("Camera position", camPos, -10.f, 10.f);
        ImGui::SliderFloat3("Camera rotation", camRot, 0.f, 360.f);
        ImGui::Checkbox("Perspective", &bPerspectiveCamera);
        
        _camera.setPosition(glm::vec3(camPos[0], camPos[1], camPos[2]));
        _camera.setRotation(glm::vec3(camRot[0],camRot[1],camRot[2]));
        _camera.setProjectionMode(bPerspectiveCamera ? Camera::Projection::Perspective : Camera::Projection::Orthographic);

        _shader1->setUniformMat4fv("viewProjMat", _camera.camViewMatrix());
        ImGui::End();

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents() ;

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(_glWindow);
    }
    
    void MainWindow::shutdown()
    {
        
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

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
