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
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::SetFloat(const char* name, float value){
    glUniform1f(glGetUniformLocation(ID, name), value);   
}

void Shader::SetVec2(const char* name, vec2 value){
    glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
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
    return std::string(std::filesystem::absolute(curr_agrv).parent_path().parent_path().parent_path()) + std::string("/") + std::string(localPath);
}