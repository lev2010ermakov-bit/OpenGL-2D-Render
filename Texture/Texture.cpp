#include "Texture.hpp"
#include <iostream>


// ----------   CONSTRUCTORS   ---------- //

Texture2D::Texture2D(){

}

Texture2D::Texture2D(const char* path, GLint colorAttribs){
    loadFromFile(path, colorAttribs);
}


// ----------   CONTROL FUNCTIONS ---------- //

void Texture2D::loadFromFile(const char* path, GLint ca){
    ColAttrib = ca;
    
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrChanels, 0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, ca, width, height, 0, ca, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        std::cerr << "Failed To Load Texture" << std::endl;
    FilePath = path;
    stbi_image_free(data);
}

void Texture2D::Bind(){
    glBindTexture(GL_TEXTURE_2D, ID);
}


// ----------   MEMORY SAFETY   ---------- //

Texture2D& Texture2D::operator=(const Texture2D& other){
    if (ID!=0) glDeleteTextures(1, &ID);
    FilePath = other.FilePath;
    ColAttrib = other.ColAttrib;

    loadFromFile(FilePath.c_str(), ColAttrib);

    return *this;
}

Texture2D& Texture2D::operator=(Texture2D&& other){
    if (ID!=0) glDeleteTextures(1, &ID);
    ID = other.ID;
    FilePath = other.FilePath;
    ColAttrib = other.ColAttrib;
    width = other.width;
    height = other.height;
    nrChanels = other.nrChanels;

    return *this;
}
