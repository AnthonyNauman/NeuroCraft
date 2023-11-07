#pragma once

#include "frame_buffer.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include <glad/include/glad/glad.h>
#include <spdlog/include/spdlog/spdlog.h>
#include <memory>

namespace nc::managers {
    class RenderManager;
}

namespace nc::graphics {
namespace renderCommands {

    class RenderCommand
    {
    public:
        virtual void execute() = 0;
        virtual ~RenderCommand() { } 
    };

    class RenderMesh : public RenderCommand
    {
    public:
        RenderMesh(std::weak_ptr<Mesh> meshPtr, std::weak_ptr<Shader> shaderPtr)
        : mMesh(meshPtr)
        , mShader(shaderPtr)
        { }

        virtual void execute() override;

    private:
        std::weak_ptr<Mesh> mMesh;
        std::weak_ptr<Shader> mShader;
        
    };

    class PushFrameBuffer : public RenderCommand
    {
    public:
        PushFrameBuffer(managers::RenderManager& rm,std::weak_ptr<FrameBuffer> fBuf) 
        : mRenderManager(rm)
        , mFrameBuffer(fBuf)
        {}

        virtual void execute() override;
    private:
        nc::managers::RenderManager& mRenderManager;
        std::weak_ptr<FrameBuffer> mFrameBuffer;
    };

    class PopFrameBuffer : public RenderCommand
    {
    public:
        PopFrameBuffer(managers::RenderManager& rm) : mRenderManager(rm){} 

        virtual void execute() override;
    private:
        nc::managers::RenderManager& mRenderManager;
    };
}
}
