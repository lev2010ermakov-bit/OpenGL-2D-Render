#pragma once

#include <SkyGraph.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>

enum direction{
    forward,
    backward,
    right,
    left,
    down,
    up
};

class CameraMover{
    public:
        CameraMover();
        CameraMover(std::shared_ptr<Camera> camera, GLFWwindow* window);
        void Update(float deltaTime);
        std::shared_ptr<Camera> camera;
        GLFWwindow* window;
        bool firstMouse = true, CursHiden = true;
        float lastx = 400.f, lasty = 300.f, x, y, mouse_sence = 0.1f, buttPand, deltaTime;
        void onCursPosChanged(GLFWwindow* window, double x, double y);
    private:
        void keyboard_moving();
        void mouse_moving();
};