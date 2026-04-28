#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string>

struct Texture2D{
    unsigned int ID;
    GLint ColAttrib;
    int width, height, nrChanels;
    std::string FilePath;

    Texture2D();
    Texture2D(const char* path, GLint colorAttrib);
    void loadFromFile(const char* path, GLint colorAttrib);
    void Bind();

    Texture2D& operator=(const Texture2D& other);
    Texture2D& operator=(Texture2D&& other);
};