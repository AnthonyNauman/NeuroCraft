#include "frame_buffer.hpp"
#include <stdint.h>
#include <glad/include/glad/glad.h>
#include "../logger.hpp"
namespace nc {

    FrameBuffer::FrameBuffer(uint32_t w, uint32_t h)
    : _width(w)
    , _height(h)
    , _FBO(0)
    , _RBO(0)
    , _textureId(0)
    , _CCR(1)
    , _CCG(1)
    , _CCB(1)
    , _CCA(1)
    {
        glGenFramebuffers(1, &_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
        
        // create color texture
        glGenTextures(1, &_textureId);
        glBindTexture(GL_TEXTURE_2D, _textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureId, 0);
        // create depth/stensil render buffer
        glGenRenderbuffers(1, &_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, _RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _RBO);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER)) 
            NC_LOG_ERROR("[_createFrameBuffer] framebuffer is not complete!!!");
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &_FBO);
        _FBO = 0;
        _RBO = 0;
        _textureId = 0;
    }

}
