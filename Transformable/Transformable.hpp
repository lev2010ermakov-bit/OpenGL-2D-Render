#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>

const glm::vec3 World_up = glm::vec3(0.0f, 1.0f, 0.0f); 

class Transformable{
    public:
        Transformable();
        Transformable(Transformable& other);
        Transformable(Transformable&& other);

        Transformable& operator=(Transformable& other);
        Transformable& operator=(Transformable&& other);

        glm::vec3 scale;
        glm::vec3 position;
        glm::vec3 eulerAngles;
        
        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 up;

        glm::mat4 GetModelMat();
        void UpdateLocalVectors();
};