#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader/Shader.hpp"
#include "Loader/Loader.hpp"
#include "CameraMover/CameraMover.hpp"
#include "Camera/Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "stb/stb_image.h"

float lastTime;
float deltaTime;

Shader shader;
Shader LampShader;
std::shared_ptr<Camera> camera;
std::shared_ptr<CameraMover> mover;
glm::mat4 trans = glm::mat4(1.0f);

glm::mat4 Mmodel = glm::mat4(1.0f);

const float Vertexes[] = {
     -0.5f,  -0.5f,  -0.5f,     0.0f,  0.0f,       0.0f,   0.0f,  -1.0f,
      0.5f,  -0.5f, -0.5f,    1.0f, 0.0f,      0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,      0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,      0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,      0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,      0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,      0.0f,  0.0f,  1.0f, 
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f,      0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 1.0f,      0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 1.0f,      0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,      0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,      0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,     -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,     -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,      1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,      1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f,      1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f,      1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f,      1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,      1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,      0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 1.0f,      0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f,      0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f,      0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,      0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,      0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,      0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,      0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,      0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,      0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,      0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,      0.0f,  1.0f,  0.0f
};

const float lampVertexes[] = {
    -0.5f, -0.5f, -0.5f, 
     0.5f, -0.5f, -0.5f,  
     0.5f,  0.5f, -0.5f,  
     0.5f,  0.5f, -0.5f,  
    -0.5f,  0.5f, -0.5f, 
    -0.5f, -0.5f, -0.5f, 
 
    -0.5f, -0.5f,  0.5f, 
     0.5f, -0.5f,  0.5f,  
     0.5f,  0.5f,  0.5f,  
     0.5f,  0.5f,  0.5f,  
    -0.5f,  0.5f,  0.5f, 
    -0.5f, -0.5f,  0.5f, 
 
    -0.5f,  0.5f,  0.5f, 
    -0.5f,  0.5f, -0.5f, 
    -0.5f, -0.5f, -0.5f, 
    -0.5f, -0.5f, -0.5f, 
    -0.5f, -0.5f,  0.5f, 
    -0.5f,  0.5f,  0.5f, 
 
     0.5f,  0.5f,  0.5f,  
     0.5f,  0.5f, -0.5f,  
     0.5f, -0.5f, -0.5f,  
     0.5f, -0.5f, -0.5f,  
     0.5f, -0.5f,  0.5f,  
     0.5f,  0.5f,  0.5f,  
 
    -0.5f, -0.5f, -0.5f, 
     0.5f, -0.5f, -0.5f,  
     0.5f, -0.5f,  0.5f,  
     0.5f, -0.5f,  0.5f,  
    -0.5f, -0.5f,  0.5f, 
    -0.5f, -0.5f, -0.5f, 
 
    -0.5f,  0.5f, -0.5f, 
     0.5f,  0.5f, -0.5f,  
     0.5f,  0.5f,  0.5f,  
     0.5f,  0.5f,  0.5f,  
    -0.5f,  0.5f,  0.5f, 
    -0.5f,  0.5f, -0.5f, 
};

void frame_buffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    camera->XtoY = (float)width/(float)height;
    mover->lastx = (float)width/2;
    mover->lasty = (float)height/2; 
}

void curs_callback(GLFWwindow* wind, double x, double y){
    mover->onCursPosChanged(wind, x, y);
}

int main(int agrc, char *agrv[])
{
    camera = std::make_shared<Camera>(60.f, 800.f/600.f, 0.1f, 100.f);  // Initializing camera class
    Camera::SetMain(camera);                                            // Set new camera as a main  

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

    mover = std::make_shared<CameraMover>(camera, window);  // Create a class that moves the camera

    glEnable(GL_DEPTH_TEST);    // enable an OpenGL depth test 

    std::shared_ptr<Texture2D> PugTex = std::make_shared<Texture2D>("Resources/Textures/PugImage.png", GL_RGBA);    // Loading a Textures From local path that always starts from "Resources"
    std::shared_ptr<Texture2D> CatTex = std::make_shared<Texture2D>("Resources/Textures/catImage.jpg", GL_RGB);     //
    std::shared_ptr<Texture2D> RockTex = std::make_shared<Texture2D>("Resources/Textures/rockImage.jpg", GL_RGB);   // 

    shader.Setup();
    shader.color = Color(116, 155, 63);

    LampShader.Setup("Resources/Shaders/LightSourceVert.glsl", "Resources/Shaders/LightSourceFrag.glsl");

    unsigned int VertexBufferObject, VertexArrayObject, LightVertexArrayObject, LightVertexBufferObject;

    glGenBuffers(1, &VertexBufferObject);                                                           // Creating buffer for vertexes attribs and sending it to video card
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);                                              //
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertexes), Vertexes, GL_STATIC_DRAW);                      //


    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);                  // Creating a VertexArray and setting instructions to reading vertex attribs
    glEnableVertexAttribArray(0);                                                                  // 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));//
    glEnableVertexAttribArray(1);                                                                  //
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));//
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &LightVertexArrayObject);                                                  // Do the same for light objects buffer and array
    glBindVertexArray(LightVertexArrayObject);                                                      //
    glGenBuffers(1, &LightVertexBufferObject);                                                      //
    glBindBuffer(GL_ARRAY_BUFFER, LightVertexBufferObject);                                         //
    glBufferData(GL_ARRAY_BUFFER, sizeof(lampVertexes), lampVertexes, GL_STATIC_DRAW);              //
                                                                                                    //
    glBindVertexArray(LightVertexArrayObject);                                                      //
    glBindBuffer(GL_ARRAY_BUFFER, LightVertexBufferObject);                                         //
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);                   //
    glEnableVertexAttribArray(0);                                                                   //

    glBindVertexArray(0);

    frame_buffer_size_callback(window, 800, 600);                                                   // calling a window scaling callback to setup our program to res 800x600
    glfwSwapInterval((float)1 / (float)144);                                                        // Setting Vsync for 144 hz monitor

    glm::vec3 positions[] = {
        glm::vec3(-1.5f, 2.f, -5.f),
        glm::vec3(3.f, -0.7f, -2.f),
        glm::vec3(0.8f, 4.f, -2.f)
    };

    glm::vec3 scales[] = {
        glm::vec3(1.1f),
        glm::vec3(2.f),
        glm::vec3(0.7f)
    };

    glm::vec3 lampPos(0.0f);
    glm::vec3 lampRot(0.0f);
    glm::vec3 lampScale(0.2f);

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
        for (int i = 0; i < positions->length(); i++)               // this cycle draws all cubes from  position and scales arrays
        {
            trans = Mmodel;
            trans = glm::translate(trans, positions[i]);
            trans = glm::rotate(trans, rot, glm::vec3(1.0f));
            trans = glm::scale(trans, scales[i]);
            float camPos[] = {Camera::main->position.x, Camera::main->position.y, Camera::main->position.z};

            shader.use();
            shader.SetColor("lightcolor", Color(255, 255, 255, 255));               // Set light color
            shader.SetFloat("ambientStrenght", 0.15f);                              // Set ambient light strenght 0...1
            shader.SetFloat("SpecularStrenght", 0.5f);                              // Set a specular coef
            shader.SetFloat("Specular", 32);                                        // Set the specular. as specular small as count is greater
            shader.SetVec3("lightPos", (float[]){lampPos.x, lampPos.y, lampPos.z}); // Set a light source pos
            shader.SetVec3("camPos", camPos);                                       // Set a view pos
            shader.SetMat4("model", trans);                                         // Set Transformation matrix to shader
            shader.SetMat4("view", Camera::main->GetView());                        // Set View matrix to make a camera moving effect
            shader.SetMat4("projection", Camera::main->GetProjection());            // Set Projection matrix to make a perspective effect

            glDrawArrays(GL_TRIANGLES, 0, 36);                                      // Drawing all points as a trianges
        }  
        
        glBindVertexArray(LightVertexArrayObject);
        trans = glm::mat4(1.f);
        trans = glm::translate(trans, lampPos);
        trans = glm::rotate(trans, lampRot.x, glm::vec3(1.f, 0.f, 0.f));
        trans = glm::rotate(trans, lampRot.y, glm::vec3(0.f, 1.f, 0.f));
        trans = glm::rotate(trans, lampRot.z, glm::vec3(0.f, 0.f, 1.f));
        trans = glm::scale(trans, lampScale);

        LampShader.use();
        LampShader.SetMat4("model", trans);
        LampShader.SetMat4("view", Camera::main->GetView());
        LampShader.SetMat4("projection", Camera::main->GetProjection());
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (buttPand > 0)
            buttPand -= deltaTime;

        if (glfwGetKey(window, GLFW_KEY_TAB) && buttPand <= 0)  // Switching a polygon mode
        {                                                       // 
            polygon = polygon ? false : true;                   //
            if (polygon)                                        //
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);      //
            else                                                //
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      //
            buttPand = 0.2f;                                    //
        }

        if (glfwGetKey(window, GLFW_KEY_1) && buttPand <= 0)    // Switching to Cat texture
        {                                                       //
            shader.SetTexture(CatTex);                          //
            buttPand = 0.2f;                                    //
        }                                                       //

        if (glfwGetKey(window, GLFW_KEY_2) && buttPand <= 0)    // Switching to Pug texture
        {                                                       //
            shader.SetTexture(PugTex);                          //
            buttPand = 0.2f;                                    //
        }                                                       //

        if (glfwGetKey(window, GLFW_KEY_3) && buttPand <= 0){
            shader.SetTexture(RockTex);
            buttPand = 0.2f;
        }

        if (glfwGetKey(window, GLFW_KEY_4) && buttPand <= 0){   // Switching to Monochrome mode
            shader.UseTexture = false;                          //
            shader.color = Color(116, 155, 63);                 //
            buttPand = 0.2f;                                    //
        }                                                       //

        deltaTime = (float)glfwGetTime() - lastTime;            // Calculation of time beetween frames
        lastTime = (float)glfwGetTime();                        //
    }
    return 0;
}