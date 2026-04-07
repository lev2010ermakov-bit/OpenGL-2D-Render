#pragma once

#include "stb/stb_image.h"
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <filesystem>

extern char* curr_agrv;

struct Texture2D{
    unsigned int ID;
    GLint ColAttrib;
    int width, height, nrChanels;
    Texture2D();
    Texture2D(const char* path, GLint colorAttrib);
    void loadFromFile(const char* path, GLint colorAttrib);
    void Bind();
};

std::string GetFullPath(const char* localPath);