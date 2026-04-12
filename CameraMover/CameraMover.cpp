#include "CameraMover.hpp"

CameraMover::CameraMover(std::shared_ptr<Camera> cam, GLFWwindow* currWindow){
    camera = cam;
    window = currWindow;
}

void CameraMover::Update(float dt){
    deltaTime = dt;
    keyboard_moving();
    mouse_moving();
}

void CameraMover::keyboard_moving(){
    if (glfwGetKey(window, GLFW_KEY_W))
    {
        camera->position += camera->front * deltaTime * 10.f;
    }
    if (glfwGetKey(window, GLFW_KEY_S))
    {
        camera->position -= camera->front * deltaTime * 10.f;
    }
    if (glfwGetKey(window, GLFW_KEY_A))
    {
        camera->position -= glm::normalize(glm::cross(camera->front, camera->up)) * 10.f * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D))
    {
        camera->position += glm::normalize(glm::cross(camera->front, camera->up)) * 10.f * deltaTime;
    }
}

void CameraMover::mouse_moving(){
    if (firstMouse)
    {
        lastx = x;
        lasty = y;
        firstMouse = false;
    }

    float xoffset = x - lastx;
    float yoffset = lasty - y;
    lastx = x;
    lasty = y;

    xoffset *= mouse_sence;
    yoffset *= mouse_sence;
    if (CursHiden)
    {
        camera->yaw -= xoffset;
        camera->pitch -= yoffset;
    }
    if (camera->pitch >= 89.999f)
        camera->pitch = 89.999f;
    else if (camera->pitch <= -89.999f)
        camera->pitch = -89.999f;
}

void CameraMover::onCursPosChanged(GLFWwindow* wind, double nx, double ny){
    x = nx;
    y = ny;
}