#include "shader.hpp"
#include "glad/include/glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm/gtc/type_ptr.hpp>



namespace nc {

    Shader::Shader(const char* vPath, const char* fPath)
    {
        std::ifstream vIs;
        std::ifstream fIs;
        std::stringstream ss;
        std::stringstream ss2;
        
        vIs.open(vPath);
        if(vIs.is_open()) {
            ss << vIs.rdbuf();
            vIs.close();
        }
        
        std::string vStr = ss.str();
        const GLchar* vCode = vStr.c_str();

        fIs.open(fPath);
        if(fIs.is_open()) {
            ss2 << fIs.rdbuf();
            fIs.close();
        }
        
        std::string fStr = ss2.str();
        const GLchar* fCode = fStr.c_str();

        GLint success;
        GLuint vs, fs;

        GLchar glLog[512];

        vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vCode, nullptr);
        glCompileShader(vs);

        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vs, 512, nullptr, glLog);
            NC_LOG_ERROR(glLog);
        }
        fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fCode, nullptr);
        glCompileShader(fs);

        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(fs, 512, nullptr, glLog);
            NC_LOG_ERROR( glLog);
        }

        _programId = glCreateProgram();
        glAttachShader(_programId, vs);
        glAttachShader(_programId, fs);
        glLinkProgram(_programId);
        glGetProgramiv(_programId, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(_programId, 512, nullptr, glLog);
            NC_LOG_ERROR(glLog);
        }
        glDeleteShader(vs);
        glDeleteShader(fs);

    }

    void Shader::useProgram()
    {
        glUseProgram(_programId);
    }

    void Shader::setUniformMat4fv(const char* name, const glm::mat4& mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(_programId, name),1, GL_FALSE, glm::value_ptr(mat));
    }

    void Shader::useUniform()
    {
        GLfloat timeValue = glfwGetTime();
        GLfloat castomColor[] = { 0.0f, (sin(timeValue) / 2) + 0.5f, 0.0f, 1.0f};
        GLint vertexColorLocation = glGetUniformLocation(_programId, "ourColor");
        glUniform4f(vertexColorLocation, castomColor[0], castomColor[1], castomColor[2], castomColor[3]);
    }

}
