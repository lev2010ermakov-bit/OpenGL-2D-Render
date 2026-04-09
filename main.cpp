#include "glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include "Shader/Shader.hpp"
#include "ResourcesLoader/Loader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float lastTime;
float deltaTime;

Shader shader;
Shader shader1;

glm::mat4 trans = glm::mat4(1.0f);
glm::mat4 trans1 = glm::mat4(1.0f);


const float Vertexes[] = {
//  Vertex Coords       Texture Coords
    0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
   -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
};

const int indices[] = {
    0, 1, 3,
    1, 2, 3
};

void frame_buffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

int main(int agrc, char* agrv[]){
    trans = glm::scale(trans, glm::vec3(0.5f * (600.f/800.f), 0.5f, 0.0f));
    trans = glm::translate(trans, glm::vec3(-0.9f));

    trans1 = glm::scale(trans1, glm::vec3(0.5f * (600.f/800.f), 0.5f, 0.0f));
    trans1 = glm::translate(trans1, glm::vec3(0.5));

    curr_agrv = agrv[0];
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

    shader.Setup();
    shader.SetTexture("Resources/Textures/PugImage.png", GL_RGBA);

    shader1.Setup();
    shader1.SetTexture("Resources/Textures/catImage.jpg", GL_RGB);

    unsigned int VertexBufferObject, VertexArrayObject, ElementBufferObject;
    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);

    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertexes), Vertexes, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &ElementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    frame_buffer_size_callback(window, 800, 600);
    glfwSwapInterval((float)1/(float)144);

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        trans = glm::rotate(trans, glm::radians(deltaTime * -125) , glm::vec3(0, 0, 1));
        shader.use();
        shader.SetMat4("trans", trans);
        glBindVertexArray(VertexArrayObject);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        //trans1 = glm::scale(trans1, glm::vec3((float)((sin(glfwGetTime())))));
        shader1.use();
        shader1.SetMat4("trans", trans1);
        glBindVertexArray(VertexArrayObject);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        deltaTime = (float)glfwGetTime() - lastTime;
        lastTime = (float)glfwGetTime();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}