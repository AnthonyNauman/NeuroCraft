#include "camera_controller.hpp"
#include "glm/ext/vector_float3.hpp"
#include <memory>



namespace nc::camera {


    CameraController::CameraController()
    {
        mCamera = std::make_shared<Camera>( glm::vec3({-10.f,0.f,0.f}), glm::vec3({0.f,0.f,0.f}), Camera::Projection::Perspective);   
    }

    void CameraController::setCameraPos(const glm::vec3& inPos)
    {
        if(mCamera)
            mCamera->setPosition(inPos);
    }
    
    void CameraController::setCameraRot(const glm::vec3& inRot)
    {
        if(mCamera)
            mCamera->setRotation(inRot);
    }

    void CameraController::xMoveCamera(const float deltaX)
    {
        if(mCamera)
            mCamera->moveX(glm::vec3({deltaX, 0.f, 0.f}));
    }

    void CameraController::yMoveCamera(const float deltaY)
    {
        if(mCamera)
            mCamera->moveY(glm::vec3({0.f, deltaY, 0.f}));
    }

    void CameraController::zMoveCamera(const float deltaZ)
    {
        if(mCamera)
            mCamera->moveZ(glm::vec3({0.f, 0.f, deltaZ}));
    }

    glm::mat4 CameraController::cameraViewMatrix()
    {
        if(mCamera)
            return mCamera->viewMatrix();
        
        return glm::mat4();
    }

}
