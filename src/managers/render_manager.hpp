#pragma once

#include <memory>
#include <queue>
#include <stack>

#include "../graphics/render_commands.hpp"

namespace nc::managers {

    class RenderManager
    {
        friend class graphics::renderCommands::PushFrameBuffer;
        friend class graphics::renderCommands::PopFrameBuffer;

    public:
        RenderManager() {}
        ~RenderManager() {}

        void init();
        void shutdown();
        //! \brief Add render command to the queue of commands.
        void submit(std::unique_ptr<graphics::renderCommands::RenderCommand> rc);
        //! \brief Execute all render commands in the queue in the order they were recieved.
        void flush();

        void clear();
        void setClearColor(float r, float g, float b, float a);

    private:
        void pushFrameBuffer(std::shared_ptr<graphics::FrameBuffer> fBuf);
        void popFrameBuffer();

    private:
        std::queue<std::unique_ptr<graphics::renderCommands::RenderCommand>> m_renderCommands;
        std::stack<std::shared_ptr<graphics::FrameBuffer>>                   m_frameBufs;
    };

}
