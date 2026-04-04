#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D Texture;
uniform vec4 color;
uniform bool UseTexture;

void main(){
    FragColor = UseTexture ? texture(Texture, TexCoords) : color;
}