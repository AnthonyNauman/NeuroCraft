#pragma once

#include "glm/glm/ext/matrix_float4x4.hpp"
#include "glm/glm/ext/vector_float3.hpp"
#include <glm/glm/vec3.hpp>
#include <glm/glm/ext/matrix_float4x3.hpp>
#include <glm/glm/trigonometric.hpp>


namespace nc::camera {

    class Camera 
    {
        public:
        enum class Projection {
            Perspective,
            Orthographic
        };
    
    public:    
        Camera(const glm::vec3& pos = {0.f,0.f,0.f}, const glm::vec3& rot = {0.f,0.f,0.f}, const Projection pMode = Projection::Perspective);
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
        void setProjectionMode(Projection pMode);
        void setPosition(const glm::vec3& pos);
        void setRotation(const glm::vec3& rot);
        void setPositionRotation(const glm::vec3& pos, const glm::vec3& rot);
        void updateViewMatrix();
        void updateProjectionMatrix();

        const glm::mat4 viewMatrix() {return _viewMat;}
        const glm::mat4 getProjMatrix() {return _projMat;}
        const glm::mat4 camViewMatrix() {return _projMat * _viewMat;}
    private:
        // World basis
        static constexpr glm::vec3 mX = glm::vec3(1.f, 0.f, 0.f);
        static constexpr glm::vec3 mY = glm::vec3(0.f, 1.f, 0.f);
        static constexpr glm::vec3 mZ = glm::vec3(0.f, 0.f, 1.f);

        glm::vec3   mCamX;
        glm::vec3   mCamY;
        glm::vec3   mCamZ;

        glm::vec3   mWorldPos;
        glm::vec3   mRot;
        Projection  mProjection;
        
        // Matrix of camera view
        glm::mat4   mVeiwMat;

        // old
        Projection  _pMode;

        
        glm::vec3   _pos;
        glm::vec3   _rot;
        glm::mat4 _viewMat;
        glm::mat4   _projMat;

        float       _r;
        float       _f;
        float       _t;
        float       _n;
        

    };
}
