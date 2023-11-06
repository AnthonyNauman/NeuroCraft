#pragma once




#include <stdint.h>
namespace nc {


    class FrameBuffer{
    public:
        FrameBuffer(uint32_t width, uint32_t height);
        ~FrameBuffer();

        inline uint32_t FBO() {return _FBO;}
        inline uint32_t RBO() {return _RBO;}
        inline uint32_t textureId() {return _textureId;}
        inline void getSize(float& w, float& h) {w = _width; h = _height;}
        inline void setColor(float r, float g, float b, float a) {_CCR = r; _CCG = g; _CCB = b; _CCA = a;}
        inline void getColor(float& r, float& g, float& b, float& a) {r = _CCR; g = _CCG; b = _CCB, a = _CCA;}

    private:
        uint32_t _FBO;
        uint32_t _RBO;
        uint32_t _textureId;
        uint32_t _width;
        uint32_t _height;
        float _CCR, _CCG, _CCB, _CCA;
    };
}
