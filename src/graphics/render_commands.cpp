#include "render_commands.hpp"
#include "frame_buffer.hpp"
#include "glad/include/glad/glad.h"
#include "../managers/render_manager.hpp"
#include "shader.hpp"
#include <memory>


namespace nc::graphics::renderCommands {

    void RenderMesh::execute()
    {
        std::shared_ptr<Mesh> mesh = mMesh.lock();
        std::shared_ptr<Shader> shader = mShader.lock();

        if(mesh && shader) {
            mesh->bind();
            shader->bind();
            if(mesh->getElementCount())
                glDrawElements(GL_TRIANGLES, mesh->getElementCount(), GL_UNSIGNED_INT, 0);
            else 
                glDrawArrays(GL_TRIANGLES /* GL_TRIANGLE_STRIP */, 0, mesh->getVertexCount());

            mesh->unbind();
            shader->unbind();

        } else
            NC_LOG_ERROR("Execution of RenderMesh with invalid data!");

    }

    void PushFrameBuffer::execute()
    {
        std::shared_ptr<graphics::FrameBuffer>fb = mFrameBuffer.lock();
        if(fb) {
            mRenderManager._pushFrameBuffer(fb);
        } else
            NC_LOG_WARN("Execution of PushFrameBuffer with invalid data!");
    }

    void PopFrameBuffer::execute()
    {
        mRenderManager._popFrameBuffer(); 
    }
}
