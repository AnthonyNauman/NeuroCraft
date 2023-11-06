#include "mesh.hpp"
#include <glad/include/glad/glad.h>
namespace nc::graphics {

    Mesh::Mesh(float* vertexArray, uint64_t vCount, uint64_t dim)
    : mVCount(vCount)
    {
        glGenVertexArrays(1, &mVAO);
        glBindVertexArray(mVAO);

        glGenBuffers(1, &mPosVBO);
        glBindBuffer(GL_ARRAY_BUFFER, mPosVBO);
        glBufferData(GL_ARRAY_BUFFER, vCount * dim * sizeof(float), vertexArray, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, dim, GL_FLOAT, GL_FALSE, 0, 0);
        glDisableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }
    
    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &mPosVBO);
        glDeleteVertexArrays(1, &mVAO);
    }

    void Mesh::bind()
    {
        glBindVertexArray(mVAO);
        glEnableVertexAttribArray(0);
    }

    void Mesh::unbind()
    {
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }

}
