#include "shader.hpp"

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

        m_programId = glCreateProgram();
        glAttachShader(m_programId, vs);
        glAttachShader(m_programId, fs);
        glLinkProgram(m_programId);
        glValidateProgram(m_programId);
        glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(m_programId, 512, nullptr, glLog);
            NC_LOG_ERROR(glLog);
            glDeleteProgram(m_programId);
        }
        glDeleteShader(vs);
        glDeleteShader(fs);
    }
    
    void Shader::bind()
    {
        glUseProgram(m_programId);
    }

    void Shader::unbind()
    {
        glUseProgram(0);
    }


    void Shader::setUniformInt(const std::string& name, int val)
    {
        glUseProgram(m_programId);
        glUniform1i(getUnifogrmLocation(name), val);
    }

    void Shader::setUniformFloat(const std::string& name, float val)
    {
        glUseProgram(m_programId);
        glUniform1f(getUnifogrmLocation(name), val);
    }

    void Shader::setUniformFloat2(const std::string& name, float val1, float val2)
    {
        glUseProgram(m_programId);
        glUniform2f(getUnifogrmLocation(name), val1, val2);

    }

    void Shader::setUniformFloat3(const std::string& name, float val1, float val2, float val3)
    {
        glUseProgram(m_programId);
        glUniform3f(getUnifogrmLocation(name), val1, val2, val3);

    }

    void Shader::setUniformFloat4(const std::string& name, float val1, float val2, float val3, float val4)
    {
        glUseProgram(m_programId);
        glUniform4f(getUnifogrmLocation(name), val1, val2, val3, val4);
    }

    void Shader::setUniformMat4fv(const std::string& name, const glm::mat4& mat)
    {
        glUseProgram(m_programId);
        glUniformMatrix4fv(getUnifogrmLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    int Shader::getUnifogrmLocation(const std::string& name)
    {
        auto it = m_uniformLocs.find(name);
        if(it == m_uniformLocs.end())
            m_uniformLocs[name] = glGetUniformLocation(m_programId, name.c_str());

        return m_uniformLocs[name];
    }
}
