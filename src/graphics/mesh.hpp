#pragma once


#include <stdint.h>
namespace nc::graphics {

    class Mesh{
    public:
        Mesh(float* vertexArray, uint64_t vCount, uint64_t dim);
        ~Mesh();
        
        inline uint64_t getVertexCount() const {return mVCount;}
        
        void bind();
        void unbind();
    private:
        uint64_t mVCount;
        uint32_t mVAO;
        uint32_t mPosVBO;
    };
}
