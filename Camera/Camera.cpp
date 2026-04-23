#include "Camera.hpp"

std::shared_ptr<Camera> Camera::main;

Camera::Camera(){
    
}

Camera::Camera(float fov, float xtoy, float near, float far){
    Fov = fov;
    Near = near;
    Far = far;
    XtoY = xtoy;
}
glm::mat4 Camera::GetView(){
    UpdateLocalVectors();
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjection(){
    UpdateLocalVectors();
    return glm::perspective(glm::radians(Fov), XtoY, Near, Far);
}

void Camera::SetMain(std::shared_ptr<Camera> camera){
    main = camera;
}