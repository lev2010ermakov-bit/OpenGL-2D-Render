#version 330 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec4 color;
uniform vec4 lightcolor;
uniform sampler2D Texture;
uniform float ambientStrenght;
uniform float SpecularStrenght;
uniform float Specular;
uniform bool UseTexture;
uniform vec3 lightPos;
uniform vec3 camPos;

out vec4 FragColor;

void main(){
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diffStrenght = max(dot(norm, lightDir), 0.0);
    vec4 difuse = diffStrenght * lightcolor;

    vec4 ambientlightRes = (ambientStrenght * lightcolor);

    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Specular);
    vec4 specular = SpecularStrenght * spec * lightcolor;


    vec4 lightRes = ambientlightRes + difuse + specular;

    if (UseTexture){
        FragColor = vec4(lightRes * texture(Texture, TexCoords));
    }
    else{
        FragColor = vec4(lightRes * color);
    }
}