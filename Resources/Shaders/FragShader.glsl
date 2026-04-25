#version 330 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

struct Material{
    vec3 AmbientColor;
    vec3 DifuseColor;
    vec3 SpecularColor;
    float Shiness;
};

struct Light{
    vec3 pos;

    vec3 ambient;
    vec3 difuse;
    vec3 specular;
};

vec4 u_Color;
uniform Material u_Material;
uniform Light u_Light;
uniform sampler2D Texture;
uniform bool UseTexture;
uniform vec3 camPos;

out vec4 FragColor;

void main(){
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_Light.pos - FragPos);

    float diffStrenght = max(dot(norm, lightDir), 0.0);
    vec4 difuse = diffStrenght * vec4(u_Light.difuse, 1) * vec4(u_Material.DifuseColor, 1.0f);

    vec4 ambientlightRes = vec4(u_Light.ambient, 1) * vec4(u_Material.AmbientColor, 1.0f);

    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shiness);
    vec4 specular = vec4(u_Light.specular, 1) * (spec * vec4(u_Material.SpecularColor, 1.0f));


    vec4 lightRes = ambientlightRes + difuse + specular;

    if (UseTexture){
        FragColor = vec4(lightRes * texture(Texture, TexCoords));
    }
    else{
        FragColor = lightRes;
    }
}