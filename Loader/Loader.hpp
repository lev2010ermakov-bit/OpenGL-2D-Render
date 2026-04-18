#pragma once

#include "../stb/stb_image.h"
#include <glad/glad.h>
#include <filesystem>
#include <string>

extern char* curr_agrv;

std::string GetFullPath(const char* localPath);