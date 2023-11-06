#pragma once

#include <memory>
#include <queue>
#include "../graphics/render_commands.hpp"
namespace nc::managers {

    class RenderManager
    {
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
        std::queue<std::unique_ptr<graphics::renderCommands::RenderCommand>> mRenderCommands; 
    };

}
