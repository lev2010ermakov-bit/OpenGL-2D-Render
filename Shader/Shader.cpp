#include "Shader.hpp"

char* curr_agrv;

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
    glBindTexture(GL_TEXTURE_2D, texture);
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

void Shader::SetBool(const char* name, bool value){
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetInt(const char* name, int value){
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetColor(const char* name, Color col){
    SetVec4(name, (float[]){(float)col.r/(float)255, (float)col.g/(float)255, (float)col.b/(float)255, (float)col.a/(float)255});
}

void Shader::SetTexture(const char* TexPath){
    SetBool("UseTexture", true);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(GetFullPath(TexPath).c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
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

std::string GetFullPath(const char* localPath){
    return std::string(std::filesystem::absolute(curr_agrv).parent_path().parent_path()) + std::string("/") + std::string(localPath);
}