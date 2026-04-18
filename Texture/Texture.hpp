#pragma once

#include <glad/glad.h>
#include "../stb/stb_image.h"
struct Texture2D{
    unsigned int ID;
    GLint ColAttrib;
    int width, height, nrChanels;
    Texture2D();
    Texture2D(const char* path, GLint colorAttrib);
    void loadFromFile(const char* path, GLint colorAttrib);
    void Bind();
};