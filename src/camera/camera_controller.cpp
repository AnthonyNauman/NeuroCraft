#include "camera_controller.hpp"
#include "glm/ext/vector_float3.hpp"

namespace nc::camera {

    CameraController::CameraController()
    {
        m_Camera = std::make_shared<Camera>(glm::vec3({ -10.f, 0.f, 0.f }), glm::vec3({ 0.f, 0.f, 0.f }));
    }

    void CameraController::setCameraPos(const glm::vec3& inPos)
    {
        if (m_Camera)
            m_Camera->setPosition(inPos);
    }

    void CameraController::setCameraRot(const glm::vec3& inRot)
    {
        if (m_Camera)
            m_Camera->setRotation(inRot);
    }

    void CameraController::xMoveCamera(const float deltaX)
    {
        if (m_Camera)
            m_Camera->moveX(glm::vec3({ deltaX, 0.f, 0.f }));
    }

    void CameraController::yMoveCamera(const float deltaY)
    {
        if (m_Camera)
            m_Camera->moveY(glm::vec3({ 0.f, deltaY, 0.f }));
    }

    void CameraController::zMoveCamera(const float deltaZ)
    {
        if (m_Camera)
            m_Camera->moveZ(glm::vec3({ 0.f, 0.f, deltaZ }));
    }

    glm::mat4 CameraController::cameraViewMatrix()
    {
        if (m_Camera)
            return m_Camera->viewMatrix();

        return glm::mat4();
    }
}
