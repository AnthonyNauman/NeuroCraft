#pragma once

#include "mesh.hpp"
#include "shader.hpp"
#include <glad/include/glad/glad.h>
#include <spdlog/include/spdlog/spdlog.h>
#include <memory>
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

}
}
