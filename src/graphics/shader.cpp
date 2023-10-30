#include "shader.hpp"
#include "glad/include/glad/glad.h"




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
        "#version 460\n"
        "in vec3 color;"
        "out vec4 frag_color;"
        "void main() {"
        "   frag_color = vec4(color, 1.0);"
        "}";

Shader::Shader(const char* _vertexShader, const char* _fragmentShader, GLfloat* _point, GLfloat* _color)
{
    GLint success; 
    GLchar infoLog[512];
    GLuint vao;
    GLchar* vertexShader;
    GLchar* fragmentShader;
    GLfloat* point;
    GLfloat* color;
    // GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vs, 1, &vertexShader, nullptr);
    // glCompileShader(vs);
    // glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    // if(!success) {
    //     glGetShaderInfoLog(vs, 512, nullptr, infoLog);
    //     __logError(infoLog);
    // }
    // GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fs, 1, &fragmentShader, nullptr);
    // glCompileShader(fs);
    // glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    // if(!success) {
    //     glGetShaderInfoLog(fs, 512, nullptr, infoLog);
    //     __logError(infoLog);
    // }
    //
    // _programId = glCreateProgram(); 
    // glAttachShader(_programId, vs);
    // glAttachShader(_programId, fs);
    // glLinkProgram(_programId);
    // glGetProgramiv(_programId, GL_LINK_STATUS, &success);
    // if(!success) {
    //     glGetProgramInfoLog(_programId, 512, nullptr, infoLog);
    //     __logError(infoLog);
    // }
    //
    // glDeleteShader(vs);
    // glDeleteShader(fs);

    //     GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vs, 1, &vertexShader, nullptr);
    //     glCompileShader(vs);
    //
    //     GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fs, 1, &fragmentShader, nullptr);
    //     glCompileShader(fs);
    //
    //     _programId = glCreateProgram();
    //     glAttachShader(_programId, vs);
    //     glAttachShader(_programId, fs);
    //     glLinkProgram(_programId);
    //
    //     glDeleteShader(vs);
    //     glDeleteShader(fs);
    // //
    //     GLuint points_vbo = 0;
    //     glGenBuffers(1, &points_vbo);
    //     glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
    //     GLuint colors_vbo = 0;
    //     glGenBuffers(1, &colors_vbo);
    //     glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    //
    //     glGenVertexArrays(1, &vao);
    //     glBindVertexArray(vao);
    //     
    //     glEnableVertexAttribArray(0);
    //     glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    //     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    //     glEnableVertexAttribArray(1);
    //     glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    //     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}


// Shader::Shader(const std::vector<float>& vShader, const std::vector<float>& fShader, float* vertises, size_t vertSize)
// {
//
// }
//
void Shader::useProgram()
{
    glUseProgram(_programId);
}

}
