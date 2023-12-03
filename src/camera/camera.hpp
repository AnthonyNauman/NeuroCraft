#pragma once

#include "glm/glm/ext/matrix_float4x4.hpp"
#include "glm/glm/ext/vector_float3.hpp"
#include <glm/glm/ext/matrix_float4x3.hpp>
#include <glm/glm/trigonometric.hpp>
#include <glm/glm/vec3.hpp>

namespace nc::camera {

    class Camera
    {
    public:
        Camera(const glm::vec3& pos = { 0.f, 0.f, 0.f }, const glm::vec3& rot = { 0.f, 0.f, 0.f }, bool bPerspective = true);
        ~Camera(){};

        // new
        //
        // move in camera coords
        void moveX(const glm::vec3 deltaX);
        void moveY(const glm::vec3 deltaY);
        void moveZ(const glm::vec3 deltaZ);

        // move and rotate in camera coords
        void moveAndRotate(const glm::vec3& trans, const glm::vec3& rot);

        /// old
        void setProjectionMode(bool bPerspective);
        void setPosition(const glm::vec3& pos);
        void setRotation(const glm::vec3& rot);
        void setPositionRotation(const glm::vec3& pos, const glm::vec3& rot);
        void updateViewMatrix();
        void updateProjectionMatrix();

        const glm::mat4 viewMatrix();
        const glm::mat4 getProjMatrix() { return m_projMat; }
        const glm::mat4 camViewMatrix() { return m_projMat * m_viewMat; }

    private:
        // World basis
        static constexpr glm::vec3 m_x = glm::vec3(1.f, 0.f, 0.f);
        static constexpr glm::vec3 m_y = glm::vec3(0.f, 1.f, 0.f);
        static constexpr glm::vec3 m_z = glm::vec3(0.f, 0.f, 1.f);

        glm::vec3 m_camX;
        glm::vec3 m_camY;
        glm::vec3 m_camZ;

        glm::vec3 m_worldPos;
        glm::vec3 m_rot;
        bool      m_bPerspective;

        // Matrix of camera view
        glm::mat4 m_veiwMat;

        // old

        glm::vec3 m_pos;
        glm::mat4 m_viewMat;
        glm::mat4 m_projMat;

        float m_r;
        float m_f;
        float m_t;
        float m_n;

        bool m_needUpdate = false;
    };
}
