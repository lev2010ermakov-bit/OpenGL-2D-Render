#pragma once

#include "../glad/include/glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <memory>
#include "../Transformable/Transformable.hpp"

class Camera : public Transformable{
    public:
        Camera();
        Camera(float FOV, float XtoY, float near, float far);

        float Fov, Near, Far, XtoY;

        static std::shared_ptr<Camera> main;

        glm::mat4 GetView();
        glm::mat4 GetProjection();
        static void SetMain(std::shared_ptr<Camera> camera);
};