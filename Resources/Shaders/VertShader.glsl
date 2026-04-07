#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 TexCoords;

uniform vec2 ScreenSize;
uniform float time;

void main(){
    float coef = ScreenSize.y/ScreenSize.x;
    //float pulse = (sin(time*(8)) + 2)/2;
    gl_Position = vec4(aPos.x * coef, aPos.y, aPos.z, 1);
    TexCoords = aTex;
}
