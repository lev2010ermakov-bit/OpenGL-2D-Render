#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 TexCoords;

uniform vec2 ScreenSize;

void main(){
    float coef = ScreenSize.y/ScreenSize.x;
    gl_Position = vec4(aPos.x * coef, aPos.y, aPos.z, 1);
    TexCoords = aTex;
}
