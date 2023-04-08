#version 450 core
layout(location = 0) out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
    vec3 VertexColour;
    vec3 Normal;
    vec3 FragPos;
} vs_out;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
struct Light{
    vec3 pos;
    vec3 colour;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
};



uniform Light light;
uniform Material material;
uniform sampler2D u_Texture;
uniform vec3 viewPos;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient * light.colour;

    // diffuse 
    vec3 normal = normalize(vs_out.Normal);
    vec3 lightDir = normalize(light.pos - vs_out.FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * light.diffuse * light.colour;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - vs_out.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
    vec3 specular = light.specular * spec * material.specular* light.colour;

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0) * texture(u_Texture, vs_out.TexCoords) * vec4(vs_out.VertexColour,1.0f);
    //FragColor = vec4(1.0,1.0,1.0,1.0f);

};