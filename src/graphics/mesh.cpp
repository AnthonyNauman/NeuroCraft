#include "mesh.hpp"
#include <glad/include/glad/glad.h>
#include <stdint.h>
namespace nc::graphics {

    Mesh::Mesh(float* vertexArray, uint64_t vCount, uint64_t dim)
    : mVCount(vCount)
    , mECount(0)
    , mEBO(0)
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
    
    Mesh::Mesh(float* vertexArray, uint64_t vCount, uint64_t dim, uint32_t* elementArray, uint64_t eCount)
    : Mesh(vertexArray, vCount, dim)
    {
        mECount = eCount;
        glBindVertexArray(mVAO);

        glGenBuffers(1, &mEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, eCount * sizeof(uint32_t), elementArray, GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &mPosVBO);
        if(mEBO)
            glDeleteBuffers(1, &mEBO);
        
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
