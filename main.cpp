#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader/Shader.hpp"

Shader shader;

const float Vertexes[] = {
    0.0f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};

const int indices[] = {
    0, 1, 2
};

void frame_buffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL 2D Render", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed To init glad" << std::endl;
    }

    unsigned int VertexBufferObject, VertexArrayObject, ElementBufferObject;
    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);

    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertexes), Vertexes, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ElementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    shader.Setup("/home/lev/Documents/CPP-Projects/OpenGL-2D-Render/Resources/Shaders/VertShader.glsl", "/home/lev/Documents/CPP-Projects/OpenGL-2D-Render/Resources/Shaders/FragShader.glsl");

    glfwSwapInterval(1/75);

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VertexArrayObject);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
