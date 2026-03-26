#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

float aspectRatio;

unsigned int ShadeProgram;

const float TriangleVert[] = {
    // Vertex Positions     //Vert Colors
     0.5f,  0.5f,  0.0f,    1.0f, 0.0f, 0.0f, 1, // Top Right
     0.5f, -0.5f,  0.0f,    1.0f, 0.0f, 1.0f, 1, // Bottom Right
    -0.5f, -0.5f,  0.0f,    0.0f, 1.0f, 0.0f, 1, // Bottom Left
    -0.5f,  0.5f,  0.0f,    0.0f, 0.0f, 1.0f, 1, // Top Left
};

const int VertexOrder[] = {
    0, 1, 2,
    2, 3, 0
};
const char* VertShaderSource = 
"#version 330\n"
"layout (location=0) in vec3 aPos;\n"
"layout (location=1) in vec4 aCol;\n"
"uniform float aspect;"
"out vec4 VertCol;"
"void main(){\n"
"   gl_Position = vec4(aPos.x*aspect, aPos.y, aPos.z, 1.0f);\n"
"   VertCol = aCol;\n"
"}\0";

const char* FragShaderSource = 
"#version 330 \n"
"out vec4 FragColor;\n"
"in vec4 VertCol;\n"
"void main(){\n"
"   FragColor = VertCol;\n"
"}\0";

void window_change_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    glUniform1f(glGetUniformLocation(ShadeProgram, "aspect"), (float)height/(float)width);
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL 2D Render", NULL, NULL);
    aspectRatio = 800/600;
    if (window == NULL){
        std::cerr << "Failed To Create A Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed To Init GLAD" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, window_change_size_callback);
    glViewport(0, 0, 800, 600);

    // Render Preparing

    unsigned int ElementBufferObject;
    ElementBufferObject;
    glGenBuffers(1, &ElementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VertexOrder), VertexOrder, GL_STATIC_DRAW);

    unsigned int VertexArrayObject;
    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);

    // 1: Copping Vertex data to memory to Buffer
    unsigned int VertexBufferObject; // create vertex buffer
    glGenBuffers(1, &VertexBufferObject); // gen it in OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject); // Bind the buffer to work with it

    glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleVert), &TriangleVert, GL_STATIC_DRAW); // load a data of shape vertexes to the video card

    // 2: Creating Genirating Compiling and linking Shaders and Shader Programm;
    // log variables
    int succsess;
    char logData[512];

    // Vertex Shader
    unsigned int VertShader;
    VertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertShader, 1, &VertShaderSource, NULL);
    glCompileShader(VertShader);

    glGetShaderiv(VertShader, GL_COMPILE_STATUS, &succsess);
    if (!succsess){
        glGetShaderInfoLog(VertShader, 512, NULL, logData);
        std::cout << "Failed To Compile Shader id=" << VertShader << " Cause: " << logData << std::endl; 
    }
    else
        std::cout << "Succsesefuly Compiled Shader id=" << VertShader << std::endl;

    // Fragment Shader
    unsigned int FragShader;
    FragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragShader, 1, &FragShaderSource, NULL);
    glCompileShader(FragShader);

    glGetShaderiv(FragShader, GL_COMPILE_STATUS, &succsess);
    if (!succsess){
        glGetShaderInfoLog(FragShader, 512, NULL, logData);
        std::cout << "Failed To Compile Shader id=" << FragShader << " Cause: " << logData << std::endl; 
    }
    else
        std::cout << "Succsesefuly Compiled Shader id=" << FragShader << std::endl;

    // Shader Program
    ShadeProgram = glCreateProgram();
    glAttachShader(ShadeProgram, VertShader);
    glAttachShader(ShadeProgram, FragShader);
    glLinkProgram(ShadeProgram);

    glGetProgramiv(ShadeProgram, GL_LINK_STATUS, &succsess);
    if (!succsess){
        glGetProgramInfoLog(ShadeProgram, 512, NULL, logData);
        std::cout << "Failed To Link Shader Program id=" << ShadeProgram << " Cause: " << logData << std::endl;
    }
    else 
        std::cout << "Shader Program Complitely Linked id=" << ShadeProgram << std::endl;

    glUseProgram(ShadeProgram);
    glUniform1f(glGetUniformLocation(ShadeProgram, "aspect"), (float)600/(float)800);

    // Deleting Shader Because they already is in the Shader Program
    glDeleteShader(VertShader);
    glDeleteShader(FragShader);

    // Setting Vertex Attrip Pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)0); // Data of Mapping our Vertex Array Positions
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(0); // Aplly the glVertexAttribPointer of VertPosition
    glEnableVertexAttribArray(1); // Apply the glVertexAttribPointer of VertColor

    // THE COOL INFORMATION

    // glVertexAttribPointer agrs:
    // 1: location in shader
    // 2: how many values attrib contain
    // 3: type of values
    // 4: need to normalize vectors?
    // 5: stride (step in memory): how many bytes needed to skip to get next value
    // 6: the first step in memory

    // !!! After the distribution each of VertexAttribPointers u need to call glEnableVertexAttribArray(n) to use this pointers !!!

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)){
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(ShadeProgram); // Use A Shaders
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject); // Bind buffer with instruction to draw
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Drawing the elements from instructions buffer

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
