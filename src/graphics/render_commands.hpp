#pragma once

#include "frame_buffer.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include <glad/include/glad/glad.h>
#include "../logger/logger.hpp"
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
            virtual ~RenderCommand() {}
        };

        class RenderMesh : public RenderCommand
        {
        public:
            RenderMesh(std::weak_ptr<Mesh> meshPtr, std::weak_ptr<Shader> shaderPtr)
              : m_mesh(meshPtr)
              , m_shader(shaderPtr)
            {}

            virtual void execute() override;

        private:
            std::weak_ptr<Mesh>   m_mesh;
            std::weak_ptr<Shader> m_shader;
        };

        class PushFrameBuffer : public RenderCommand
        {
        public:
            PushFrameBuffer(managers::RenderManager& rm, std::weak_ptr<FrameBuffer> fBuf)
              : m_renderManager(rm)
              , m_frameBuffer(fBuf)
            {}

            virtual void execute() override;

        private:
            nc::managers::RenderManager& m_renderManager;
            std::weak_ptr<FrameBuffer>   m_frameBuffer;
        };

        class PopFrameBuffer : public RenderCommand
        {
        public:
            PopFrameBuffer(managers::RenderManager& rm)
              : m_renderManager(rm)
            {}

            virtual void execute() override;

        private:
            nc::managers::RenderManager& m_renderManager;
        };
    }
}
