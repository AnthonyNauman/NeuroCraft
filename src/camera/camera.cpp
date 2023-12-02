#include "camera.hpp"

namespace nc::camera {

    Camera::Camera(const glm::vec3& pos, const glm::vec3& rot, bool bPerspective)
      : m_worldPos(pos)
      , m_rot(rot)
      , m_bPerspective(bPerspective)
    {
        updateViewMatrix();
    }

    void Camera::moveX(const glm::vec3 deltaX) { m_worldPos += m_camX * deltaX; }

    void Camera::moveY(const glm::vec3 deltaY) { m_worldPos += m_camY * deltaY; }

    void Camera::moveZ(const glm::vec3 deltaZ) { m_worldPos += m_camZ * deltaZ; }

    void Camera::moveAndRotate(const glm::vec3& trans, const glm::vec3& rot)
    {
        m_worldPos += m_camX * trans.x;
        m_worldPos += m_camY * trans.y;
        m_worldPos += m_camZ * trans.z;

        m_rot += rot;
    }

    void Camera::setPosition(const glm::vec3& pos) { m_pos = pos; }

    void Camera::setRotation(const glm::vec3& rot) { m_rot = rot; }

    void Camera::setPositionRotation(const glm::vec3& pos, const glm::vec3& rot)
    {
        m_pos = pos;
        m_rot = rot;
    }

    void Camera::setProjectionMode(bool bPerspective)
    {
        m_bPerspective = bPerspective;
        updateProjectionMatrix();
    }

    const glm::mat4 Camera::viewMatrix()
    {
        if (m_needUpdate) {
            updateViewMatrix();
        }

        return m_veiwMat;
    }

    void Camera::updateViewMatrix()
    {
        // clang-format off
        glm::mat4 translateMatrix(
            1,          0,          0,          0,
            0,          1,          0,          0,
            0,          0,          1,          0,
            -m_pos[0],   -m_pos[1],   -m_pos[2],   1
        );

        float xRot = glm::radians(-m_rot.x);
        glm::mat4 rotationXMatrix(
            cos(xRot),            sin(xRot),        0,      0,
            -sin(xRot),           cos(xRot),        0,      0,
            0,                      0,              1,      0,
            0,                      0,              0,      1
        );
        float yRot = glm::radians(-m_rot.y);
        glm::mat4 rotationYMatrix(
            cos(yRot),            sin(yRot),        0,      0,
            -sin(yRot),           cos(yRot),        0,      0,
            0,                      0,              1,      0,
            0,                      0,              0,      1
        );
        float zRot = glm::radians(-m_rot.z);
        glm::mat4 rotationZMatrix( cos(zRot),            sin(zRot),        0,      0,
                                   -sin(zRot),           cos(zRot),        0,      0,
                                            0,                   0,        1,      0,
                                             0,                  0,        0,      1);
        // clang-format on

        m_viewMat = rotationYMatrix * rotationXMatrix * translateMatrix;
    }

    void Camera::updateProjectionMatrix()
    {
        if (m_bPerspective) {
            m_r = 0.1f;
            m_t = 0.1f;
            m_f = 10.0f;
            m_n = 0.1f;

            // clang-format off
            m_projMat = glm::mat4(m_n/m_r,          0,                         0,              0,
                                        0,    m_n/m_t,                         0,              0,
                                        0,          0,      (-m_f-m_n)/(m_f-m_n),             -1,
                                        0,          0,      -2*m_f*m_n/(m_f-m_n),              0);

        } else {

            m_r = 2.0f;
            m_t = 2.0f;
            m_f = 100.0f;
            m_n = 0.1f;

m_projMat = glm::mat4(1/m_r,          0,                          0,              0,
                          0,       1/m_t,                         0,              0,
                          0,           0,              -2/(m_f-m_n),              0,
                          0,           0,      (-m_f-m_n)/(m_f-m_n),              1);
            // clang-format on
        }
    }
}
