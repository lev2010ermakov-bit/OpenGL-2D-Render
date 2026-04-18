#include "Shader.hpp"
#include "glad/glad.h"

Shader::Shader(){
}

Shader::Shader(Shader&& other){
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

void Shader::Setup(const char* VertPath, const char* FragPath){
    std::ifstream VertFile, FragFile;
    std::string VertString, FragString;

    VertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    FragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        VertFile.open(GetFullPath(VertPath));
        FragFile.open(GetFullPath(FragPath));

        std::stringstream VertStream, FragStream;

        VertStream << VertFile.rdbuf();
        FragStream << FragFile.rdbuf();

        VertFile.close();
        FragFile.close();

        VertSourceString = VertString;
        FragSourceString = FragString;

        VertString = VertStream.str();
        FragString = FragStream.str();
    }
    catch(std::ifstream::failure& ex){
        std::cout << "Failed To Read Shader Files\n";
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
    Setup("Resources/Shaders/VertShader.glsl", "Resources/Shaders/FragShader.glsl");
}

void Shader::use(){
    if (texture) texture->Bind();
    SetColor("color", color);
    SetBool("UseTexture", UseTexture);
    SetFloat("time", (float)glfwGetTime());
    glUseProgram(ID);
}

void Shader::SetFloat(const char* name, float value){
    glUniform1f(glGetUniformLocation(ID, name), value);   
}

void Shader::SetVec2(const char* name, float value[2]){
    glUniform2f(glGetUniformLocation(ID, name), value[0], value[1]);
}

void Shader::SetVec3(const char* name, float value[3]){
    glUniform3f(glGetUniformLocation(ID, name), value[0], value[1], value[2]);
}

void Shader::SetVec4(const char* name, float value[4]){
    glUniform4f(glGetUniformLocation(ID, name), value[0], value[1], value[2], value[3]);
}

void Shader::SetMat4(const char* name, glm::mat4 value){
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
}



void Shader::SetBool(const char* name, bool value){
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetInt(const char* name, int value){
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetColor(const char* name, Color col){
    SetVec4(name, (float[]){(float)col.r/(float)255, (float)col.g/(float)255, (float)col.b/(float)255, (float)col.a/(float)255});
}

void Shader::SetTexture(std::shared_ptr<Texture2D> ntexture){
    texture = ntexture;
    UseTexture = true;
}

// need to write that operators
Shader& Shader::operator=(Shader&& other){
}

Shader& Shader::operator=(const Shader& other){

}

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