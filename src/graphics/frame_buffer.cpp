#include "frame_buffer.hpp"

namespace nc::graphics {

    FrameBuffer::FrameBuffer(uint32_t w, uint32_t h)
    : m_width(w)
    , m_height(h)
    , m_FBO(0)
    , m_RBO(0)
    , m_textureId(0)
    , m_CCR(1)
    , m_CCG(1)
    , m_CCB(1)
    , m_CCA(1)
    {
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
        
        // create color texture
        glGenTextures(1, &m_textureId);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0);
        // create depth/stensil render buffer
        glGenRenderbuffers(1, &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
            NC_LOG_ERROR("[_createFrameBuffer] framebuffer is not complete!!!");
        } 
               
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &m_FBO);
        m_FBO = 0;
        m_RBO = 0;
        m_textureId = 0;
    }

}
