#include "render_commands.hpp"
#include "glad/include/glad/glad.h"
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

            glDrawArrays(GL_TRIANGLES /* GL_TRIANGLE_STRIP */, 0, mesh->getVertexCount());

            mesh->unbind();
            shader->unbind();

        } else {
            NC_LOG_ERROR("Execution of RenderMesh with invalid data!");
        }

    }

}
