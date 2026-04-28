#include "ColorChoise.hpp"
#include <iostream>

ColorChoise::ColorChoise(){

}

ColorChoise::ColorChoise(GLFWwindow* wind, Material* mat, Shader* shade){
    window = wind;
    shaderMat = mat;
    shader = shade;
}

void ColorChoise::Update(float deltaTime){
    if (!window || !shaderMat || !shader) return;
    if (glfwGetKey(window, GLFW_KEY_T) && buttPand <= 0){
        colorDebug = !colorDebug;
        if (colorDebug) std::cout << "debug: Color Debuging turn ON" << std::endl;
        else            std::cout << "debug: Color Debuging turn OFF" << std::endl;
        buttPand = 0.2f;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) && buttPand <= 0 && colorDebug){
        currentColDebug--;
        if (currentColDebug < 0){
            currentColDebug = 2;
        }
        std::cout << "debug: color turned ";
        switch (currentColDebug){
            case 0: std::cout << "Ambient Color";  break;
            case 1: std::cout << "Difuse Color";   break;
            case 2: std::cout << "Specular Color"; break;
        }
        std::cout << std::endl;
        buttPand = 0.2f;
    }

    if (glfwGetKey(window, GLFW_KEY_E) && buttPand <= 0 && colorDebug){
        currentColDebug++;
        if (currentColDebug > 2){
            currentColDebug = 0;
        }
        std::cout << "debug: color turned ";
        switch (currentColDebug){
            case 0: std::cout << "Ambient Color";  break;
            case 1: std::cout << "Difuse Color";   break;
            case 2: std::cout << "Specular Color"; break;
        }
        std::cout << std::endl;
        buttPand = 0.2f;
    }

    if (glfwGetKey(window, GLFW_KEY_R) && buttPand <= 0 && colorDebug){
        currentColItem = 0;
        std::cout << "debug: color item turned ";
        switch (currentColItem){
            case 0: std::cout << "Red";   break;
            case 1: std::cout << "Green"; break;
            case 2: std::cout << "Blue";  break;
        }
        std::cout << std::endl;
        buttPand = 0.2f;
    }

    if (glfwGetKey(window, GLFW_KEY_G) && buttPand <= 0 && colorDebug){
        currentColItem = 1;
        std::cout << "debug: color item turned ";
        switch (currentColItem){
            case 0: std::cout << "Red";   break;
            case 1: std::cout << "Green"; break;
            case 2: std::cout << "Blue";  break;
        }
        std::cout << std::endl;
        buttPand = 0.2f;
    }

    if (glfwGetKey(window, GLFW_KEY_B) && buttPand <= 0 && colorDebug){
        currentColItem = 2;
        std::cout << "debug: Color item turned ";
        switch (currentColItem){
            case 0: std::cout << "Red";   break;
            case 1: std::cout << "Green"; break;
            case 2: std::cout << "Blue";  break;
        }
        std::cout << std::endl;
        buttPand = 0.2f;
    }

    if (glfwGetKey(window, GLFW_KEY_EQUAL) && buttPand <= 0 && colorDebug){
        glm::vec3* CurrMatColor;
        std::cout << "debug: ";
        switch (currentColDebug){
            case 0: CurrMatColor = &shaderMat->AmbientColor; std::cout << "AmbientColor.";   break;
            case 1: CurrMatColor = &shaderMat->DifuseColor; std::cout << "DifuseColor.";     break;
            case 2: CurrMatColor = &shaderMat->SpecularColor; std::cout << "SpecularColor."; break;
        }
        switch (currentColItem){
            case 0: CurrMatColor->x += 5.f/255.f; std::cout << "r = " << round(CurrMatColor->x * 255.f); break;
            case 1: CurrMatColor->y += 5.f/255.f; std::cout << "g = " << round(CurrMatColor->y * 255.f); break;
            case 2: CurrMatColor->z += 5.f/255.f; std::cout << "b = " << round(CurrMatColor->z * 255.f); break;
        }
        std::cout << std::endl;
        shader->SetVec3("u_Material.AmbientColor", shaderMat->AmbientColor);
        shader->SetVec3("u_Material.DifuseColor", shaderMat->DifuseColor);
        shader->SetVec3("u_Material.SpecularColor", shaderMat->SpecularColor);
        buttPand = 0.05f;
    }

    if (glfwGetKey(window, GLFW_KEY_MINUS) && buttPand <= 0 && colorDebug){
        glm::vec3* CurrMatColor;
        std::cout << "debug: ";
        switch (currentColDebug){
            case 0: CurrMatColor = &shaderMat->AmbientColor; std::cout << "AmbientColor.";  break;
            case 1: CurrMatColor = &shaderMat->DifuseColor; std::cout << "DifuseColor.";    break;
            case 2: CurrMatColor = &shaderMat->SpecularColor; std::cout << "SpecularColor."; break;
        }
        switch (currentColItem){
            case 0: CurrMatColor->x -= 5.f/255.f; std::cout << "r = " << round(CurrMatColor->x * 255.f); break;
            case 1: CurrMatColor->y -= 5.f/255.f; std::cout << "g = " << round(CurrMatColor->y * 255.f); break;
            case 2: CurrMatColor->z -= 5.f/255.f; std::cout << "b = " << round(CurrMatColor->z * 255.f); break;
        }
        std::cout << std::endl;
        shader->SetVec3("u_Material.AmbientColor",  shaderMat->AmbientColor);
        shader->SetVec3("u_Material.DifuseColor",   shaderMat->DifuseColor);
        shader->SetVec3("u_Material.SpecularColor", shaderMat->SpecularColor);
        buttPand = 0.05f;
    }
    if (buttPand > 0)
        buttPand -= deltaTime;
}