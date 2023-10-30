#include "main_window.hpp"
#include "iostream"

#include "../utils.hpp"
#include "../logger.hpp"
#include "../libs/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include <memory>
#include <vector>

namespace nc {

    GLfloat point[] = {
        0.0f,   0.5f,   0.0f,
        0.5f,   -0.5f,  0.0f,
        -0.5f,  -0.5f,  0.0f
    }; 
    GLfloat color[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f
    };
    
    GLfloat* color2;
    
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };
    const char* vertex_shader=
        "#version 460\n"
        "layout(location = 0) in vec3 vertex_position;"
        "layout(location = 1) in vec3 vertex_color;"
        "out vec3 color;"
        "void main() {"
        "   color = vertex_color;"
        "   gl_Position = vec4(vertex_position, 1.0);"
        "}";

    const char* fragment_shader=
        "#version 460 core\n"
        "in vec3 color;"
        "out vec4 frag_color;"
        "void main() {"
        "   frag_color = vec4(color, 1.0);"
        "}";

    GLuint _programId;
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
            __logCritical("Can't init Glad"); 
        }
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); 
        //! @note Добавить флаг докинга
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(_glWindow, true);
        ImGui_ImplOpenGL3_Init(_glslVersion);
        std::string vertShaderStr= 
        "#version 460 core\n"
        "layout(location = 0) in vec3 vertex_position;"
        "layout(location = 1) in vec3 vertex_color;"
        "out vec3 color;"
        "void main() {"
        "   color = vertex_color;"
        "   gl_Position = vec4(vertex_position, 1.0);"
        "}";
        
        std::string fragShaderStr = 
        "#version 460 core\n"
        "in vec3 color;"
        "out vec4 frag_color;"
        "void main() {"
        "   frag_color = vec4(color, 1.0);"
        "}";

        std::vector<float> vecVert= {

        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

        const char* vShader = vertShaderStr.c_str();
        const char* fShader = fragShaderStr.c_str();
        // _shader1 = new Shader(vertex_shader, fragment_shader, point, color);
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vShader,nullptr);
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fShader, nullptr);
        glCompileShader(fs);

        _programId = glCreateProgram();
        glAttachShader(_programId, vs);
        glAttachShader(_programId, fs);
        glLinkProgram(_programId);

        glDeleteShader(vs);
        glDeleteShader(fs);
    //
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
        // _shader1->useProgram();
        // glUniform1f(glGetUniformLocation(_shader1->programId(), "someUniform"), 1.0f);
        glUseProgram(_programId);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents() ;

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        


        //! @todo MyStaff
        ImGui::Begin("test");
        ImGui::Button("test");
        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        // glfwGetFramebufferSize(_glWindow, &display_w, &display_h);
        // glViewport(0, 0, display_w, display_h);
        // glClearColor(0,0.5,0.5,1);
        // glClear(GL_COLOR_BUFFER_BIT);
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
