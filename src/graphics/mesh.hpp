#pragma once


#include <stdint.h>
namespace nc::graphics {

    class Mesh{
    public:
        Mesh(float* vertexArray, uint64_t vCount, uint64_t dim);
        Mesh(float* vertexArray, uint64_t vCount, uint64_t dim, uint32_t* elementArray, uint64_t eCount);
        ~Mesh();
        
        inline uint64_t getVertexCount() const {return mVCount;}
        inline uint64_t getElementCount() const {return mECount;}
        
        void bind();
        void unbind();
    private:
        uint64_t mVCount, mECount;
        uint32_t mVAO, mEBO;
        uint32_t mPosVBO;
    };
}
