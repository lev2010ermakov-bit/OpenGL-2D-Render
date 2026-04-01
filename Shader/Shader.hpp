#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <fstream>
#include <string>

class Shader{
    public:
        int ID;
        Shader();
        Shader(const char* VertPath, const char* FragPath);
        void Setup(const char* VertPath, const char* FragPath);
        void use();
};

void ShaderLog(int Shader);