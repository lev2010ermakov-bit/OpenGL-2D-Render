#include "Texture.hpp"
#include <string>
#include "../Loader/Loader.hpp"
#include <iostream>

Texture2D::Texture2D(){

}

Texture2D::Texture2D(const char* path, GLint colorAttribs){
    loadFromFile(path, colorAttribs);
}

void Texture2D::loadFromFile(const char* path, GLint ca){
    ColAttrib = ca;
    
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::string globalPath = GetFullPath(path);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(globalPath.c_str(), &width, &height, &nrChanels, 0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, ca, width, height, 0, ca, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        std::cerr << "Failed To Load Texture" << std::endl;
    
    stbi_image_free(data);
}

void Texture2D::Bind(){
    glBindTexture(GL_TEXTURE_2D, ID);
}
