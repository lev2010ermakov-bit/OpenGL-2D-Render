#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <stdint.h>
#include <memory>
#include <Texture.hpp>


struct Color{
    uint8_t r = 255, g = 255, b = 255, a = 255;
    Color(){}
    Color(uint8_t red, uint8_t green, uint8_t blue){ r = red; g = green; b = blue; a = 255; } 
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {r = red; g = green; b = blue; a = alpha; }
};

class Shader{
    private:
        std::string VertSourceString;
        std::string FragSourceString;
    public:
        unsigned int ID = 0;
        bool UseTexture = false;
        std::shared_ptr<Texture2D> texture = nullptr;
        Color color = Color();
        Shader();
        Shader(const Shader& other);
        Shader(const Shader&& other);
        Shader(const char* VertPath, const char* FragPath);
        void Setup(const char* VertPath, const char* FragPath);
        void Setup();
        void use();

        void SetFloat(const char* name, float value);
        
        void SetVec2(const char* name, float value[2]);
        void SetVec2(const char* name, glm::vec2 value);
        
        void SetVec3(const char* name, float value[3]);
        void SetVec3(const char* name, glm::vec3 value);

        void SetVec4(const char* name, float value[4]);
        void SetVec4(const char* name, glm::vec4 value);

        void SetMat3(const char* name, glm::mat3 value);
        void SetMat4(const char* name, glm::mat4 value);

        void SetBool(const char* name, bool value);
        void SetInt(const char* name, int value);

        void SetColor(const char* name, Color col);

        void SetTexture(std::shared_ptr<Texture2D> texture);

        Shader& operator=(const Shader& other);
        Shader& operator=(Shader&& other);
};

void ShaderLog(int Shader);

std::string GetFullPath(const char* localPath);