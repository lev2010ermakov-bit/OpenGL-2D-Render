#version 330 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec4 color;
uniform vec4 lightcolor;
uniform sampler2D Texture;
uniform float ambientStrenght;
uniform bool UseTexture;
uniform vec3 lightPos;

out vec4 FragColor;

void main(){
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diffStrenght = max(dot(norm, lightDir), 0.0);
    vec4 difuse = diffStrenght * lightcolor;

    vec4 ambientlightRes = (ambientStrenght * lightcolor);
    vec4 lightRes = ambientlightRes + difuse;
    if (UseTexture){
        FragColor = vec4(lightRes * texture(Texture, TexCoords));
    }
    else{
        FragColor = vec4(lightRes * color);
    }
}