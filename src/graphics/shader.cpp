#include "shader.hpp"
#include "glad/include/glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm/gtc/type_ptr.hpp>



namespace nc::graphics{

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

        fIs.open(fPath);
        if(fIs.is_open()) {
            ss2 << fIs.rdbuf();
            fIs.close();
        }
        
        std::string fStr = ss2.str();
        
        const GLchar* vCode = vStr.c_str();
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

        mProgramId = glCreateProgram();
        glAttachShader(mProgramId, vs);
        glAttachShader(mProgramId, fs);
        glLinkProgram(mProgramId);
        glValidateProgram(mProgramId);
        glGetProgramiv(mProgramId, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(mProgramId, 512, nullptr, glLog);
            NC_LOG_ERROR(glLog);
            glDeleteProgram(mProgramId);
        }
        glDeleteShader(vs);
        glDeleteShader(fs);
    }
    
    void Shader::bind()
    {
        glUseProgram(mProgramId);
    }

    void Shader::unbind()
    {
        glUseProgram(0);
    }


    void Shader::setUniformInt(const std::string& name, int val)
    {
        glUseProgram(mProgramId);
        glUniform1i(_getUnifogrmLocation(name), val);
    }

    void Shader::setUniformFloat(const std::string& name, float val)
    {
        glUseProgram(mProgramId);
        glUniform1f(_getUnifogrmLocation(name), val);
    }

    void Shader::setUniformFloat2(const std::string& name, float val1, float val2)
    {
        glUseProgram(mProgramId);
        glUniform2f(_getUnifogrmLocation(name), val1, val2);

    }

    void Shader::setUniformFloat3(const std::string& name, float val1, float val2, float val3)
    {
        glUseProgram(mProgramId);
        glUniform3f(_getUnifogrmLocation(name), val1, val2, val3);

    }

    void Shader::setUniformFloat4(const std::string& name, float val1, float val2, float val3, float val4)
    {
        glUseProgram(mProgramId);
        glUniform4f(_getUnifogrmLocation(name), val1, val2, val3, val4);
    }

    void Shader::setUniformMat4fv(const std::string& name, const glm::mat4& mat)
    {
        glUseProgram(mProgramId);
        glUniformMatrix4fv(_getUnifogrmLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    int Shader::_getUnifogrmLocation(const std::string& name)
    {
        auto it = mUniformLocs.find(name);
        if(it == mUniformLocs.end())
            mUniformLocs[name] = glGetUniformLocation(mProgramId, name.c_str());

        return mUniformLocs[name];
    }

}
