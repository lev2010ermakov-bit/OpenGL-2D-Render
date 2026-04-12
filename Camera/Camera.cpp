#include "Camera.hpp"

std::shared_ptr<Camera> Camera::main;

Camera::Camera(){

}

Camera::Camera(float fov, float xtoy, float near, float far){
    Fov = fov;
    Near = near;
    Far = far;
    XtoY = xtoy;
    world_up = up;
}

void Camera::update_vectors(){
    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(dir);
    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(front, right));
}

glm::mat4 Camera::GetView(){
    update_vectors();
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjection(){
    update_vectors();
    return glm::perspective(glm::radians(Fov), XtoY, Near, Far);
}

void Camera::SetMain(std::shared_ptr<Camera> camera){
    main = camera;
}