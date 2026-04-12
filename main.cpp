#include "glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include "Shader/Shader.hpp"
#include "ResourcesLoader/Loader.hpp"
#include "CameraMover/CameraMover.hpp"
#include "Camera/Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float lastTime;
float deltaTime;

Shader shader;
std::shared_ptr<Camera> camera;
std::shared_ptr<CameraMover> mover;
glm::mat4 trans = glm::mat4(1.0f);

glm::mat4 Mmodel = glm::mat4(1.0f);

const float Vertexes[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

const int indices[] = {
    0, 1, 3,
    1, 2, 3};

void frame_buffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    camera->XtoY = (float)width/(float)height;
    mover->lastx = (float)width/2;
    mover->lasty = (float)height/2; 
}

float mouse_sence = 0.1f;

void curs_callback(GLFWwindow* wind, double x, double y){
    mover->onCursPosChanged(wind, x, y);
}
int main(int agrc, char *agrv[])
{
    camera = std::make_shared<Camera>(60.f, 800.f/600.f, 0.1f, 100.f);
    Camera::SetMain(camera);

    curr_agrv = agrv[0];
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL 2D Render", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed To init glad" << std::endl;
    }

    mover = std::make_shared<CameraMover>(camera, window);

    glEnable(GL_DEPTH_TEST);

    std::shared_ptr<Texture2D> PugTex = std::make_shared<Texture2D>("Resources/Textures/PugImage.png", GL_RGBA);
    std::shared_ptr<Texture2D> CatTex = std::make_shared<Texture2D>("Resources/Textures/catImage.jpg", GL_RGB);

    shader.Setup();
    shader.SetTexture(PugTex);

    unsigned int VertexBufferObject, VertexArrayObject, ElementBufferObject;
    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);

    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertexes), Vertexes, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &ElementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    frame_buffer_size_callback(window, 800, 600);
    glfwSwapInterval((float)1 / (float)144);

    glm::vec3 positions[] = {
        glm::vec3(-0.7f, 0.8f, -5.f),
        glm::vec3(-0.9f, -0.7f, -2.f),
        glm::vec3(0.8f, 0.9f, -2.f)};

    glm::vec3 scales[] = {
        glm::vec3(0.5f),
        glm::vec3(2.f),
        glm::vec3(0.7f)};

    bool polygon;
    float buttPand;

    float rot;

    camera->yaw = -90;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, curs_callback);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rot += deltaTime;
        mover->Update(deltaTime);

        glBindVertexArray(VertexArrayObject);

        for (int i = 0; i < positions->length(); i++)
        {
            trans = Mmodel;
            trans = glm::translate(trans, positions[i]);
            trans = glm::rotate(trans, rot, glm::vec3(1.0f));
            trans = glm::scale(trans, scales[i]);

            shader.SetMat4("model", trans);
            shader.SetMat4("view", camera->GetView());
            shader.SetMat4("projection", camera->GetProjection());

            shader.use();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);

        deltaTime = (float)glfwGetTime() - lastTime;
        lastTime = (float)glfwGetTime();

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (buttPand > 0)
            buttPand -= deltaTime;

        if (glfwGetKey(window, GLFW_KEY_TAB) && buttPand <= 0)
        {
            polygon = polygon ? false : true;
            if (polygon)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            buttPand = 0.2f;
        }

        if (glfwGetKey(window, GLFW_KEY_1))
        {
            shader.SetTexture(CatTex);
            buttPand = 0.2f;
        }
        if (glfwGetKey(window, GLFW_KEY_2))
        {
            shader.SetTexture(PugTex);
            buttPand = 0.2f;
        }


        if ((glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwGetKey(window, GLFW_KEY_LEFT_SUPER)) && buttPand <= 0)
        {
            if (mover->CursHiden)
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                mover->firstMouse = true;
            }
            mover->CursHiden = mover->CursHiden ? false : true;
            buttPand = 0.2f;
    }
    }
    return 0;
}