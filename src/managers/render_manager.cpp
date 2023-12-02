#include "render_manager.hpp"

namespace nc::managers {
    
    void RenderManager::init()
    {
        NC_LOG_INFO("OpenGL info:\n  Vendor:\t{}\n  Renderer:\t{}\n  Version:\t{}\n"
                    , reinterpret_cast<const char*>(glGetString(GL_VENDOR))
                    , reinterpret_cast<const char*>(glGetString(GL_RENDERER))
                    , reinterpret_cast<const char*>(glGetString(GL_VERSION))
                    );

        // glEnable(GL_DEPTH_TEST);
        // glDepthFunc(GL_LEQUAL);

        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        setClearColor(static_cast<float>(0x64) / static_cast<float>(0xFF)
                     ,static_cast<float>(0x95) / static_cast<float>(0xFF)
                     ,static_cast<float>(0xED) / static_cast<float>(0xFF)
                     , 1.f
                      );
    }

    void RenderManager::shutdown()
    {
        while (m_renderCommands.size()) {
            m_renderCommands.pop();

        }
    }

    void RenderManager::submit(std::unique_ptr<graphics::renderCommands::RenderCommand> rc)
    {
        m_renderCommands.push(std::move(rc));
    }

    void RenderManager::flush()
    {
        while (m_renderCommands.size()) {
            auto rc = std::move(m_renderCommands.front());
            m_renderCommands.pop();
            rc->execute();
        }
    }

    void RenderManager::clear()
    {
        while (m_renderCommands.size())
            m_renderCommands.pop();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderManager::setClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void RenderManager::pushFrameBuffer(std::shared_ptr<graphics::FrameBuffer> fBuf)
    {
        m_frameBufs.push(fBuf);
        glBindFramebuffer(GL_FRAMEBUFFER, fBuf->FBO());

        float r,g,b,a;
        fBuf->getColor(r, g, b, a);
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void RenderManager::popFrameBuffer()
    {
        if(m_frameBufs.size()) {
            m_frameBufs.pop();

            if(m_frameBufs.size()) {
                auto nextBuf = m_frameBufs.top();
                glBindFramebuffer(GL_FRAMEBUFFER, nextBuf->FBO());
            } else 
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
        } 
    }
}
