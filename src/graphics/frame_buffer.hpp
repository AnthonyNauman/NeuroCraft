#pragma once

#include <stdint.h>

#include <glad/include/glad/glad.h>

#include "../logger.hpp"

namespace nc::graphics {

    class FrameBuffer{
    public:
        FrameBuffer(uint32_t width, uint32_t height);
        ~FrameBuffer();

        inline uint32_t FBO() {return m_FBO;}
        inline uint32_t RBO() {return m_RBO;}
        inline uint32_t textureId() {return m_textureId;}
        inline void getSize(float& w, float& h) {w = m_width; h = m_height;}
        inline void setColor(float r, float g, float b, float a) {m_CCR = r; m_CCG = g; m_CCB = b; m_CCA = a;}
        inline void getColor(float& r, float& g, float& b, float& a) {r = m_CCR; g = m_CCG; b = m_CCB, a = m_CCA;}

    private:
        uint32_t m_FBO;
        uint32_t m_RBO;
        uint32_t m_textureId;
        uint32_t m_width;
        uint32_t m_height;
        float m_CCR, m_CCG, m_CCB, m_CCA;
    };
}
