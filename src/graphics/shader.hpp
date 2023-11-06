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
#include <string>
#include <unordered_map>
#include <vector>
#define GL_SILENCE_DEPRECATION


namespace nc::graphics{

class Shader{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader(){}
    
    void bind();
    void unbind();


    inline void useProgram() {glUseProgram(mProgramId);}
    
    void setUniformInt(const std::string& name, int val);
    void setUniformFloat(const std::string& name, float val);
    void setUniformFloat2(const std::string& name, float val1, float val2);
    void setUniformFloat3(const std::string& name, float val1, float val2, float val3);
    void setUniformFloat4(const std::string& name, float val1, float val2, float val3, float val4);
    void setUniformMat4fv(const std::string& name, const glm::mat4& mat);
private:
    int _getUnifogrmLocation(const std::string& name);
private:
    
    GLuint mProgramId;
    std::unordered_map<std::string, int> mUniformLocs;
    // GLuint mVS;
    // GLuint mFS;


};
}
