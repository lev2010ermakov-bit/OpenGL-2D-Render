#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include "Shader/Shader.hpp"
#include "Loader/Loader.hpp"
#include "CameraMover/CameraMover.hpp"
#include "Camera/Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>
#include "Transformable/Transformable.hpp"
#include "stb/stb_image.h"
#include "cubeData.h"
#include "Material/Material-struct.hpp"
#include "RuntimeColorChoise/ColorChoise.hpp"

float lastTime;
float deltaTime;

bool colorDebug;
int currentColDebug;
int currentColItem;

Shader shader;
Shader shader2;
Shader LampShader;

ColorChoise colChoiser;

Material shaderMat;

std::shared_ptr<Camera> camera;
CameraMover mover;

void frame_buffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    camera->XtoY = (float)width/(float)height;
    mover.lastx = (float)width/2;
    mover.lasty = (float)height/2; 
}

void curs_callback(GLFWwindow* wind, double x, double y){
    mover.onCursPosChanged(wind, x, y);
}

int main(int agrc, char *agrv[])
{
    camera = std::make_shared<Camera>(60.f, 800.f/600.f, 0.1f, 100.f);  // Initializing camera class
    Camera::SetMain(camera);                                            // Set new camera as a main  
    camera->position = glm::vec3(-3.31473, -1.567f, 6.05006f);
    camera->eulerAngles = glm::vec3(14.9043f, -61.7206f, 0.0f);

    curr_agrv = agrv[0];
    glfwInit();                                                     // Initializing a glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // Set version of programm context to 3 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  //
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Set Profile of programm context to core

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL 2D Render", NULL, NULL);    // Create a small window
    glfwMakeContextCurrent(window);                                                     // Give a program focuse to window
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);                 // Set a window scaling callback

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))                            // Load glad function uses a glfw
    {
        std::cout << "Failed To init glad" << std::endl;                                // error log
    }

    mover = CameraMover(camera, window);  // Create a class that moves the camera

    glEnable(GL_DEPTH_TEST);    // enable an OpenGL depth test 

    unsigned int VertexBufferObject, VertexArrayObject, LightVertexArrayObject, LightVertexBufferObject;

    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vtn_cube_vertexes), vtn_cube_vertexes, GL_STATIC_DRAW);


    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &LightVertexArrayObject);
    glBindVertexArray(LightVertexArrayObject);
    glGenBuffers(1, &LightVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, LightVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v_cube_vertexes), v_cube_vertexes, GL_STATIC_DRAW);
    glBindVertexArray(LightVertexArrayObject);                                                                           //
    glBindBuffer(GL_ARRAY_BUFFER, LightVertexBufferObject);                                                      //
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);  //
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    frame_buffer_size_callback(window, 800, 600);                                               // calling a window scaling callback to setup our program to res 800x600
    glfwSwapInterval((float)1 / (float)144);                                                        // Setting Vsync for 144 hz monitor

    std::vector<Transformable> cubes = std::vector<Transformable>(3);

    cubes[0].position = glm::vec3(-1.5f, 2.f, -5.f);
    cubes[0].scale = glm::vec3(1.1f);

    cubes[1].position = glm::vec3(3.f, -0.7f, -2.f);
    cubes[1].scale = glm::vec3(2.f);

    cubes[2].position = glm::vec3(0.8f, 4.f, -2.f);
    cubes[2].scale = glm::vec3(0.7f);

    Transformable Lamp;
    Lamp.scale = glm::vec3(0.2f);

    bool polygon;
    float buttPand;

    float rot;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, curs_callback);

    colChoiser.window = window;
    colChoiser.shader = &shader;
    colChoiser.shaderMat = &shaderMat;

    std::shared_ptr<Texture2D> PugTex = std::make_shared<Texture2D>(GetFullPath("Resources/Textures/PugImage.png").c_str(), GL_RGBA);    // Loading a Textures
    std::shared_ptr<Texture2D> CatTex = std::make_shared<Texture2D>(GetFullPath("Resources/Textures/catImage.jpg").c_str(), GL_RGB);     //
    std::shared_ptr<Texture2D> RockTex = std::make_shared<Texture2D>(GetFullPath("Resources/Textures/rockImage.jpg").c_str(), GL_RGB);   // 

    shader.Setup();
    shader.color = Color(116, 155, 63);

    shader2 = shader;

    LampShader.Setup(GetFullPath("Resources/Shaders/UnlitVertShader.glsl").c_str(), GetFullPath("Resources/Shaders/UnlitFragShader.glsl").c_str());
    LampShader.color = Color(255, 255, 255);

    shaderMat.AmbientColor = glm::vec3(1.0f);
    shaderMat.DifuseColor = glm::vec3(1.0f);
    shaderMat.SpecularColor = glm::vec3(1.0f);
    shaderMat.Shiness = 256.f;

    shader.SetVec3("u_Material.AmbientColor", shaderMat.AmbientColor);
    shader.SetVec3("u_Material.DifuseColor", shaderMat.DifuseColor);
    shader.SetVec3("u_Material.SpecularColor", shaderMat.SpecularColor);
    shader.SetFloat("u_Material.Shiness", shaderMat.Shiness);

    shader.SetVec3("u_Light.ambient",  glm::vec3(0.2f));
    shader.SetVec3("u_Light.difuse",  glm::vec3(1.f));
    shader.SetVec3("u_Light.specular", glm::vec3(0.3f));
    shaderMat.Shiness = 256.f;

    shader2.SetVec3("u_Material.AmbientColor", shaderMat.AmbientColor);
    shader2.SetVec3("u_Material.DifuseColor", shaderMat.DifuseColor);
    shader2.SetVec3("u_Material.SpecularColor", shaderMat.SpecularColor);
    shader2.SetFloat("u_Material.Shiness", shaderMat.Shiness);

    shader2.SetVec3("u_Light.ambient",  glm::vec3(0.2f));
    shader2.SetVec3("u_Light.difuse",  glm::vec3(1.f));
    shader2.SetVec3("u_Light.specular", glm::vec3(0.3f));

    LampShader.SetColor("u_Color", LampShader.color);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rot += deltaTime;

        mover.Update(deltaTime);
        colChoiser.Update(deltaTime);

        glBindVertexArray(VertexArrayObject);
        for (int i = 0; i < cubes.capacity(); i++)               // this cycle draws all cubes from  position and scales arrays
        {
            float camPos[] = {Camera::main->position.x, Camera::main->position.y, Camera::main->position.z};
            if (i==0){
            shader2.use();
            shader2.SetColor("lightcolor", LampShader.color);                                              // Set light color
            shader2.SetFloat("ambientStrenght", 0.15f);                                                  // Set ambient light strenght 0...1
            shader2.SetFloat("SpecularStrenght", 0.5f);                                                  // Set a specular coef
            shader2.SetFloat("Specular", 32);                                                            // Set the specular. as specular small as count is greater
            shader2.SetVec3("u_Light.pos", (float[]){Lamp.position.x, Lamp.position.y, Lamp.position.z});   // Set a light source pos
            shader2.SetVec3("camPos", camPos);                                                           // Set a view pos
            shader2.SetMat4("u_Model", cubes[i].GetModelMat());                                          // Set Transformation matrix to shader
            shader2.SetMat4("u_View", Camera::main->GetView());                                          // Set View matrix to make a camera moving effect
            shader2.SetMat4("u_Projection", Camera::main->GetProjection());
            }
            else
            {
            shader.use();
            shader.SetColor("lightcolor", LampShader.color);                                              // Set light color
            shader.SetFloat("ambientStrenght", 0.15f);                                                  // Set ambient light strenght 0...1
            shader.SetFloat("SpecularStrenght", 0.5f);                                                  // Set a specular coef
            shader.SetFloat("Specular", 32);                                                            // Set the specular. as specular small as count is greater
            shader.SetVec3("u_Light.pos", (float[]){Lamp.position.x, Lamp.position.y, Lamp.position.z});   // Set a light source pos
            shader.SetVec3("camPos", camPos);                                                           // Set a view pos
            shader.SetMat4("u_Model", cubes[i].GetModelMat());                                          // Set Transformation matrix to shader
            shader.SetMat4("u_View", Camera::main->GetView());                                          // Set View matrix to make a camera moving effect
            shader.SetMat4("u_Projection", Camera::main->GetProjection());
            }
            glDrawArrays(GL_TRIANGLES, 0, 36);                                                    // Drawing all points as a trianges
        }  
        
        glBindVertexArray(LightVertexArrayObject);

        LampShader.use();
        LampShader.SetMat4("u_Model", Lamp.GetModelMat());
        LampShader.SetMat4("u_View", Camera::main->GetView());
        LampShader.SetMat4("u_Projection", Camera::main->GetProjection());
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (buttPand > 0)
            buttPand -= deltaTime;

        if (glfwGetKey(window, GLFW_KEY_TAB) && buttPand <= 0)     // Switching a polygon mode
        {                                                               // 
            polygon = polygon ? false : true;                           //
            if (polygon)                                                //
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);   //
            else                                                        //
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);   //
            buttPand = 0.2f;                                            //
        }

        if (glfwGetKey(window, GLFW_KEY_1) && buttPand <= 0)    // Switching to Cat texture
        {                                                           //
            shader.SetTexture(CatTex);                              //
            buttPand = 0.2f;                                        //
        }                                                           //

        if (glfwGetKey(window, GLFW_KEY_2) && buttPand <= 0)    // Switching to Pug texture
        {                                                           //
            shader.SetTexture(PugTex);                              //
            buttPand = 0.2f;                                        //
        }                                                           //

        if (glfwGetKey(window, GLFW_KEY_3) && buttPand <= 0){
            shader.SetTexture(RockTex);
            buttPand = 0.2f;
        }

        if (glfwGetKey(window, GLFW_KEY_4) && buttPand <= 0){   // Switching to Monochrome mode
            shader.UseTexture = false;                              //
            shader.color = Color(116, 155, 63);     //
            buttPand = 0.2f;                                        //
        }                                                           //

        if (glfwGetKey(window, GLFW_KEY_L) && buttPand <= 0){
            std::cout << "pos: " << camera->position.x << " " << camera->position.y << " " << camera->position.z << std::endl;
            std::cout << "rot: " << camera->eulerAngles.x << " " << camera->eulerAngles.y << " " << camera->eulerAngles.z << std::endl;
            buttPand = 0.2f;
        }

        deltaTime = (float)glfwGetTime() - lastTime;                // Calculation of time beetween frames
        lastTime = (float)glfwGetTime();                            //
    }
    return 0;
}