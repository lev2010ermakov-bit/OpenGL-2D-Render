#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 TexCoords;

uniform float time;
uniform mat4 trans;

void main(){
    gl_Position = trans * vec4(aPos.x, aPos.y, aPos.z, 1);
    TexCoords = aTex;
}
