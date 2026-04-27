#include "Shader.hpp"
#include "glad/glad.h"
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>


// ---------- CONSTRUCTORS ---------- //

Shader::Shader(){
}

Shader::Shader(const Shader&& other){
    ID = other.ID;
    texture = other.texture;
    UseTexture = other.UseTexture;
    color = other.color;
}

Shader::Shader(const Shader& other){
    VertSourceString = other.VertSourceString;
    FragSourceString = other.FragSourceString;

    const char* VertChars = VertSourceString.c_str();
    const char* FragChars = FragSourceString.c_str();

    unsigned int vertshade, fragshade;
    ID = glCreateProgram();

    vertshade = glCreateShader(GL_VERTEX_SHADER);
    fragshade = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertshade, 1, &VertChars, NULL);
    glCompileShader(vertshade);
    ShaderLog(vertshade);

    glShaderSource(fragshade, 1, &FragChars, NULL);
    glCompileShader(fragshade);
    ShaderLog(fragshade);

    glAttachShader(ID, vertshade);
    glAttachShader(ID, fragshade);
    glLinkProgram(ID);

    glDeleteShader(vertshade);
    glDeleteShader(vertshade);
    color = Color(0, 0, 0, 255);
}

Shader::Shader(const char* VertPath, const char* FragPath){
    Setup(VertPath, FragPath);
}


// ---------- CONTROL FUNCTIONS ---------- //

void Shader::Setup(const char* VertPath, const char* FragPath){
    std::ifstream VertFile, FragFile;
    std::string VertString, FragString;

    VertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    FragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        VertFile.open(VertPath);
        FragFile.open(FragPath);

        std::stringstream VertStream, FragStream;

        VertStream << VertFile.rdbuf();
        FragStream << FragFile.rdbuf();

        VertFile.close();
        FragFile.close();

        VertString = VertStream.str();
        FragString = FragStream.str();

        VertSourceString = VertString;
        FragSourceString = FragString;
    }
    catch(std::ifstream::failure& ex){
        std::cout << "Failed To Read Shader Files:" << VertPath << " " << FragPath << std::endl;
        return;
    }

    const char* VertSource = VertString.c_str();
    const char* FragSource = FragString.c_str();

    unsigned int VertShader, FragShader;
    ID = glCreateProgram();

    VertShader = glCreateShader(GL_VERTEX_SHADER);
    FragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(VertShader, 1, &VertSource, NULL);
    glCompileShader(VertShader);
    ShaderLog(VertShader);
    
    glShaderSource(FragShader, 1, &FragSource, NULL);
    glCompileShader(FragShader);
    ShaderLog(FragShader);

    glAttachShader(ID, VertShader);
    glAttachShader(ID, FragShader);
    glLinkProgram(ID);

    glDeleteShader(VertShader);
    glDeleteShader(FragShader);
    color = Color(0, 0, 0, 255);
}

void Shader::Setup(){
    Setup(GetFullPath("Resources/Shaders/VertShader.glsl").c_str(), GetFullPath("Resources/Shaders/FragShader.glsl").c_str());
}

void Shader::use(){
    glUseProgram(ID);
    if (texture) texture->Bind();
    SetBool("UseTexture", UseTexture);
    SetFloat("time", (float)glfwGetTime());
}

// ----------   VECTORS   ---------- //

void Shader::SetVec2(const char* name, float value[2]){                                         // VECTOR 2
    glUseProgram(ID);
    glUniform2f(glGetUniformLocation(ID, name), value[0], value[1]);
}
void Shader::SetVec2(const char* name, glm::vec2 value){
    glUseProgram(ID);
    glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
}


void Shader::SetVec3(const char* name, float value[3]){                                         // VECTOR 3
    glUseProgram(ID);  
    glUniform3f(glGetUniformLocation(ID, name), value[0], value[1], value[2]);
}
void Shader::SetVec3(const char* name, glm::vec3 value){
    glUseProgram(ID);
    glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
}


void Shader::SetVec4(const char* name, float value[4]){                                         // VECTOR 4
    glUseProgram(ID);
    glUniform4f(glGetUniformLocation(ID, name), value[0], value[1], value[2], value[3]);
}
void Shader::SetVec4(const char* name, glm::vec4 value){
    glUseProgram(ID);
    glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.a);
}


// ----------   MATRIX   ---------- //

void Shader::SetMat3(const char* name, glm::mat3 value){                                        // MATRIX 3x3
    glUseProgram(ID);
    glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(const char* name, glm::mat4 value){                                        // MATRIX 4x4
    glUseProgram(ID);
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
}


// ----------   FUNDAMENTAL TYPES   ---------- //

void Shader::SetFloat(const char* name, float value){                                           // FLOAT
    glUseProgram(ID);
    glUniform1f(glGetUniformLocation(ID, name), value);   
}
void Shader::SetBool(const char* name, bool value){                                             // BOOL                  
    glUseProgram(ID);
    glUniform1i(glGetUniformLocation(ID, name), value);
}
void Shader::SetInt(const char* name, int value){                                               // INT
    glUseProgram(ID);
    glUniform1i(glGetUniformLocation(ID, name), value);
}


// ----------   CUSTOM TYPES ---------- //

void Shader::SetColor(const char* name, Color col){                                             // COLOR
    SetVec4(name, (float[]){(float)col.r/(float)255, (float)col.g/(float)255, (float)col.b/(float)255, (float)col.a/(float)255});
}

void Shader::SetTexture(std::shared_ptr<Texture2D> ntexture){                                   // TEXTURE
    texture = ntexture;
    UseTexture = true;
}


// ----------  MEMORY SAFETY  ---------- //

Shader& Shader::operator=(Shader&& other){
    if (ID != 0) glDeleteProgram(ID);
    ID = other.ID;
    color = other.color;
    texture = other.texture;
    UseTexture = other.UseTexture;
    VertSourceString = other.VertSourceString;
    FragSourceString = other.FragSourceString;
    return *this;
}

Shader& Shader::operator=(const Shader& other){
    if (ID != 0) glDeleteProgram(ID);
    VertSourceString = other.VertSourceString;
    FragSourceString = other.FragSourceString;

    ID = glCreateProgram();
    unsigned int vs, fs;
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vert_source = VertSourceString.c_str();
    const char* frag_source = FragSourceString.c_str();

    glShaderSource(vs, 1, &vert_source, NULL);
    glCompileShader(vs);

    glShaderSource(fs, 1, &frag_source, NULL);
    glCompileShader(fs);

    glAttachShader(ID, vs);
    glAttachShader(ID, fs);
    glLinkProgram(ID);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return *this;
}


// ---------- LOG ---------- //
void ShaderLog(int Shader){
    char log[512];
    int succsess;

    glGetShaderiv(Shader, GL_COMPILE_STATUS, &succsess);
    if (!succsess){
        glGetShaderInfoLog(Shader, 512, NULL, log);
        std::cout << "Failed To Compile Shader id=" << Shader << " Cause: " << log << std::endl;
    }
    else{
        std::cout << "Shader Succsessefully Compiled id =" << Shader << std::endl;
    }
}