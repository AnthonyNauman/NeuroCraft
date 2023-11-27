#include "camera.hpp"
#include "glm/glm/ext/matrix_float4x4.hpp"

namespace nc::camera {

    Camera::Camera(const glm::vec3& pos, const glm::vec3& rot, const Projection pMode )
    : mWorldPos(pos)
    , mRot(rot)
    , mProjection(pMode)
    {
        updateViewMatrix();
    }

void Camera::moveX(const glm::vec3 deltaX)
{
    mWorldPos += mCamX * deltaX;
}

void Camera::moveY(const glm::vec3 deltaY)
{
    mWorldPos += mCamY * deltaY;
}

void Camera::moveZ(const glm::vec3 deltaZ)
{
    mWorldPos += mCamZ * deltaZ;
}

void Camera::moveAndRotate(const glm::vec3& trans, const glm::vec3& rot)
{
        mWorldPos += mCamX * trans.x;
        mWorldPos += mCamY * trans.y;
        mWorldPos += mCamZ * trans.z;

        mRot += rot;
}

    void Camera::setPosition(const glm::vec3& pos)
    {
        _pos = pos;
        updateViewMatrix();
    }
    
    void Camera::setRotation(const glm::vec3& rot)
    {
        _rot = rot;
        updateViewMatrix();
    }
    
    void Camera::setPositionRotation(const glm::vec3& pos, const glm::vec3& rot)
    {
        _pos = pos;
        _rot = rot;
        updateViewMatrix();
    }
    
    void Camera::setProjectionMode(Projection pMode)
    {
        _pMode = pMode;
        updateProjectionMatrix();
    }

    void Camera::updateViewMatrix()
    {
        glm::mat4 translateMatrix(
            1,          0,          0,          0,
            0,          1,          0,          0,
            0,          0,          1,          0,
            -_pos[0],   -_pos[1],   -_pos[2],   1
        );
        
        float xRot = glm::radians(-_rot.x);
        glm::mat4 rotationXMatrix(
            cos(xRot),            sin(xRot),        0,      0,
            -sin(xRot),           cos(xRot),        0,      0,
            0,                      0,              1,      0,
            0,                      0,              0,      1
        );
        float yRot = glm::radians(-_rot.y);
        glm::mat4 rotationYMatrix(
            cos(yRot),            sin(yRot),        0,      0,
            -sin(yRot),           cos(yRot),        0,      0,
            0,                      0,              1,      0,
            0,                      0,              0,      1
        );
        float zRot = glm::radians(-_rot.z);
        glm::mat4 rotationZMatrix(
            cos(zRot),            sin(zRot),        0,      0,
            -sin(zRot),           cos(zRot),        0,      0,
            0,                      0,              1,      0,
            0,                      0,              0,      1
        );

        
        _viewMat = rotationYMatrix * rotationXMatrix * translateMatrix; 
    }
    
    void Camera::updateProjectionMatrix()
    {
        if(_pMode == Projection::Perspective) {
            _r = 0.1f;
            _t = 0.1f;
            _f = 10.0f;
            _n = 0.1f;

            _projMat = glm::mat4(_n/_r,          0,                         0,              0,
                                     0,      _n/_t,                         0,              0,
                                     0,          0,          (-_f-_n)/(_f-_n),             -1,
                                     0,          0,          -2*_f*_n/(_f-_n),             0);


        } else {
            
            _r = 2.0f;
            _t = 2.0f;
            _f = 100.0f;
            _n = 0.1f;

            _projMat = glm::mat4(1/_r,          0,                         0,              0,
                                     0,      1/_t,                         0,              0,
                                     0,          0,               -2/(_f-_n),              0,
                                     0,          0,         (-_f-_n)/(_f-_n),             1);
        }
    }

}
