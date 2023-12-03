#pragma once

#include "camera.hpp"

#include "glm/glm/detail/qualifier.hpp"
#include "glm/glm/ext/matrix_float4x4.hpp"
#include "glm/glm/ext/vector_float3.hpp"
#include <glm/glm/ext/matrix_float4x3.hpp>
#include <glm/glm/trigonometric.hpp>
#include <glm/glm/vec3.hpp>
#include <memory>

namespace nc::camera {

    class CameraController
    {
    public:
        CameraController();
        ~CameraController() {}

        void setCameraPos(const glm::vec3& inPos);
        void setCameraRot(const glm::vec3& inRot);
        // Move camera in camera coordinates
        void xMoveCamera(const float deltaX);
        void yMoveCamera(const float deltaY);
        void zMoveCamera(const float deltaZ);

        glm::mat4 cameraViewMatrix();

    private:
        std::shared_ptr<Camera> m_Camera;
    };
}
