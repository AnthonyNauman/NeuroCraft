#pragma once

#include "glm/glm/detail/qualifier.hpp"
#include "glm/glm/ext/matrix_float4x4.hpp"
#include "glm/glm/ext/vector_float3.hpp"
#include <glm/glm/vec3.hpp>
#include <glm/glm/ext/matrix_float4x3.hpp>
#include <glm/glm/trigonometric.hpp>


namespace nc {

    class Camera 
    {
        public:
        enum class Projection {
            Perspective,
            Orthographic
        };
    
    public:    
        Camera(const glm::vec3& pos = {0,0,0}, const glm::vec3& rot = {0,0,0}, const Projection pMode = Projection::Perspective);
        ~Camera(){};

        void setProjectionMode(Projection pMode);
        void setPosition(const glm::vec3& pos);
        void setRotation(const glm::vec3& rot);
        void setPositionRotation(const glm::vec3& pos, const glm::vec3& rot);
        void updateViewMatrix();
        void updateProjectionMatrix();

        const glm::mat4 getViewMatrix() {return _viewMat;}
        const glm::mat4 getProjMatrix() {return _projMat;}
        const glm::mat4 camViewMatrix() {return _projMat * _viewMat;}
    private:
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
