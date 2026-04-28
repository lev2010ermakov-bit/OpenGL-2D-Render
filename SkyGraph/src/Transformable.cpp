#include <Transformable.hpp>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/matrix.hpp>


// ----------   CONSTRUCTORS   ---------- //
Transformable::Transformable(){
    scale = glm::vec3(1);
    position = glm::vec3(0);
    eulerAngles = glm::vec3(0);
}


// ----------   OUTPUT FUNCTIONS ---------- //
glm::mat4 Transformable::GetModelMat(){
    glm::mat4 res = glm::mat4(1);

    res = glm::translate(res, position);
    res = glm::rotate(res, eulerAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
    res = glm::rotate(res, eulerAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
    res = glm::rotate(res, eulerAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));
    res = glm::scale(res, scale);

    return res;
}


// ----------   SYSTEM FUNCTIONS   ---------- // 
void Transformable::UpdateLocalVectors(){
    glm::vec3 dir;
    dir.x = cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
    dir.y = sin(glm::radians(eulerAngles.x));
    dir.z = sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
    front = glm::normalize(dir);
    right = glm::normalize(glm::cross(front, World_up));
    up = glm::normalize(glm::cross(front, right));
}