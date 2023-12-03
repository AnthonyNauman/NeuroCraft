#pragma once

#include <stdint.h>

namespace nc::graphics {

    class Mesh
    {
    public:
        Mesh(float* vertexArray, uint64_t vCount, uint64_t dim);
        Mesh(float* vertexArray, uint64_t vCount, uint64_t dim, uint32_t* elementArray, uint64_t eCount);
        ~Mesh();

        inline uint64_t getVertexCount() const { return m_vCount; }
        inline uint64_t getElementCount() const { return m_eCount; }

        void bind();
        void unbind();

    private:
        uint64_t m_vCount, m_eCount;
        uint32_t m_VAO, m_EBO;
        uint32_t m_posVBO;
    };
}
