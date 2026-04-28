#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main(){
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0f);
    FragPos = vec3(u_Model * vec4(aPos, 1.0f)); 
    TexCoords = aTex;
    Normal = mat3(transpose(inverse(u_Model))) * aNorm;
}
