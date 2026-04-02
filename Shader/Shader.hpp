#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>

extern char* curr_agrv;

struct vec2{
    float x, y;
    vec2(float x, float y);
};

class Shader{
    public:
        int ID;
        Shader();
        Shader(const char* VertPath, const char* FragPath);
        void Setup(const char* VertPath, const char* FragPath);
        void use();

        void SetFloat(const char* name, float value);
        void SetVec2(const char* name, vec2 value);
};

void ShaderLog(int Shader);

std::string GetFullPath(const char* localPath);