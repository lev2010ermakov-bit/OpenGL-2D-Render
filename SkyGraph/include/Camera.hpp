#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <Transformable.hpp>

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