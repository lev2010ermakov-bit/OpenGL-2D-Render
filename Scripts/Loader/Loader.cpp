#include "Loader.hpp"
#include <filesystem>

char* curr_agrv;

std::string GetFullPath(const char* localPath){
    return std::string(std::filesystem::absolute(curr_agrv).parent_path().parent_path().parent_path()) + std::string("/") + std::string(localPath);
}