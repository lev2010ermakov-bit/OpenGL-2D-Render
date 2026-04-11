#include "Shader.hpp"

vec2::vec2(float nx, float ny){
    x = nx;
    y = ny;
}

Shader::Shader(){
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
    color = Color(255, 200, 100, 100);
    SetVec4("color", (float[]){1, 1, 1, 1});
    UseTexture = false;
}

void Shader::Setup(){
    Setup("Resources/Shaders/VertShader.glsl", "Resources/Shaders/FragShader.glsl");
}

void Shader::use(){
    texture->Bind();
    SetColor("color", color);
    SetBool("UseTexture", UseTexture);
    SetFloat("time", (float)glfwGetTime());
    glUseProgram(ID);
}

void Shader::SetFloat(const char* name, float value){
    glUniform1f(glGetUniformLocation(ID, name), value);   
}

void Shader::SetVec2(const char* name, vec2 value){
    glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
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