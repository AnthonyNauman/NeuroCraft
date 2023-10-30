#pragma once

#include "../utils.hpp"
#include "../logger.hpp"
#include "../libs/glad/include/glad/glad.h"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3_loader.h>

#include <GLFW/glfw3.h> 
#include <vector>
#define GL_SILENCE_DEPRECATION


namespace nc{

class Shader{
public:
    Shader(const char* vertexShader, const char* fragmentShader, GLfloat* point, GLfloat* color);
    // Shader(const std::vector<float>& vShader, const std::vector<float>& fShader, const std::vector<float>& vertices);
    ~Shader(){}
    void useProgram();
    const GLuint programId() {return _programId;}

private:
    GLuint _programId;
    GLuint _vertexShader;
    GLuint _fragmentShader;
};
}
