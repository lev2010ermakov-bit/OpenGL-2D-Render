#pragma once

#include <glm/glm.hpp>

struct Material{
    public:
        glm::vec3 AmbientColor = glm::vec3(1.f);
        glm::vec3 DifuseColor = glm::vec3(1.f);
        glm::vec3 SpecularColor = glm::vec3(1.f);
        float Shiness = 32.f;
};