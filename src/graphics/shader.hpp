#pragma once

#include "../utils.hpp"
#include "../logger.hpp"
#include "../libs/glad/include/glad/glad.h"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3_loader.h>

 #include <glm/glm/ext/matrix_float4x4.hpp>

#include <GLFW/glfw3.h> 
#include <vector>
#define GL_SILENCE_DEPRECATION


namespace nc{

class Shader{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader(){}
    void useProgram();
    const GLuint program() {return _programId;}
    void setUniformMat4fv(const char* name, const glm::mat4& mat);
    void useUniform();
private:
    
    GLuint _programId;
    GLuint _vs;
    GLuint _fs;


};
}