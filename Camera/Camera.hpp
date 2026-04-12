#pragma once

#include "../glad/include/glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <memory>

class Camera{
    public:
        Camera();
        Camera(float FOV, float XtoY, float near, float far);

        float Fov, Near, Far, XtoY;

        static std::shared_ptr<Camera> main;

        glm::vec3 position = glm::vec3(0.0f, 0.0f, -3.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f); 
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 right;
        glm::vec3 world_up;
        float yaw, pitch;

        glm::mat4 GetView();
        glm::mat4 GetProjection();
        static void SetMain(std::shared_ptr<Camera> camera);
    private:
        void update_vectors();
};