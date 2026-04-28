#version 330 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

struct Material{
    bool hasDiff;
    vec4 DiffuseColor;
    sampler2D DiffuseMap;

    bool hasSpec;
    float Specular;
    sampler2D SpecularMap;

    bool hasEmis;
    sampler2D EmissionMap;


    float Shiness;
};

struct Light{
    vec3 pos;

    vec3 ambient;
    vec3 difuse;
    vec3 specular;
};

uniform Material u_Material;
uniform Light u_Light;
uniform vec3 camPos;

out vec4 FragColor;

void main(){
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_Light.pos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse_res;
    vec3 ambient_res;

    if (u_Material.hasDiff){
        ambient_res = u_Light.ambient * texture(u_Material.DiffuseMap, TexCoords).xyz;
        diffuse_res = diff * texture(u_Material.DiffuseMap, TexCoords).xyz;
    }
    else{
        ambient_res = u_Light.ambient * vec3(u_Material.DiffuseColor);
        diffuse_res = diff * vec3(u_Material.DiffuseColor);
    }

    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shiness);
    vec3 specular_res;
    if (u_Material.hasSpec)
        specular_res = u_Light.specular * (spec * texture(u_Material.SpecularMap, TexCoords).xyz);
    else 
        specular_res = u_Light.specular * (spec * u_Material.Specular);

    vec3 emision_res;
    if (u_Material.hasEmis)
        emision_res = texture(u_Material.EmissionMap, TexCoords).xyz;

    vec4 lightRes = vec4(ambient_res + diffuse_res + specular_res + emision_res, 1.0f);

    FragColor = lightRes;
}