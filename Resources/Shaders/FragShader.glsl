#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D Texture;
uniform vec4 color;
uniform vec4 lightcolor;
uniform bool UseTexture;
uniform float ambientStrenght;

void main(){
    vec4 res = (ambientStrenght * lightcolor) * color;
    FragColor = UseTexture ? texture(Texture, TexCoords) : res;
}