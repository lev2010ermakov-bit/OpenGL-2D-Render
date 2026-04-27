#pragma once

#include <SkyGraph.hpp>
#include <GLFW/glfw3.h>

class ColorChoise{
    public:
        GLFWwindow* window;
        Material* shaderMat;
        Shader* shader;
        float buttPand;
        bool colorDebug;
        int currentColDebug, currentColItem;

        ColorChoise();
        ColorChoise(GLFWwindow* wind, Material* mat, Shader* shade);
        void Update(float deltaTime);
};