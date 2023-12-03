#include "mesh.hpp"
#include <glad/include/glad/glad.h>
#include <stdint.h>

namespace nc::graphics {

    Mesh::Mesh(float* vertexArray, uint64_t vCount, uint64_t dim)
      : m_vCount(vCount)
      , m_eCount(0)
      , m_EBO(0)
    {
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_posVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_posVBO);
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
        m_eCount = eCount;
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, eCount * sizeof(uint32_t), elementArray, GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &m_posVBO);
        if (m_EBO)
            glDeleteBuffers(1, &m_EBO);

        glDeleteVertexArrays(1, &m_VAO);
    }

    void Mesh::bind()
    {
        glBindVertexArray(m_VAO);
        glEnableVertexAttribArray(0);
    }

    void Mesh::unbind()
    {
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }
}
