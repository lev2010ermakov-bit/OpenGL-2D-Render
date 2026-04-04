#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>
#include <stdint.h>
#include "../stb/stb_image.h"

extern char* curr_agrv;

struct vec2{
    float x, y;
    vec2(float x, float y);
};

struct Color{
    uint8_t r = 255, g = 255, b = 255, a = 255;
    Color(){}
    Color(uint8_t red, uint8_t green, uint8_t blue){ r = red; g = green; b = blue; a = 255; } 
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {r = red; g = green; b = blue; a = alpha; }
};

class Shader{
    public:
        unsigned int ID;
        unsigned int texture;
        bool UseTexture;
        Color color;
        Shader();
        Shader(const char* VertPath, const char* FragPath);
        void Setup(const char* VertPath, const char* FragPath);
        void Setup();
        void use();

        void SetFloat(const char* name, float value);
        void SetVec2(const char* name, vec2 value);
        void SetVec4(const char* name, float value[4]);
        void SetBool(const char* name, bool value);
        void SetInt(const char* name, int value);
        void SetColor(const char* name, Color col);
        void SetTexture(const char* TexPath);
};

void ShaderLog(int Shader);

std::string GetFullPath(const char* localPath);