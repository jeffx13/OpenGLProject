#version 330 core
layout(location = 0) out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

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
uniform vec3 view_pos;

uniform sampler2D texture_normal0;
uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;

void main()
{
    vec3 normal = normalize(texture(texture_normal0,fs_in.TexCoords).xyz * 2.0f - 1.0f);
    // ambient

    // diffuse 
    vec3 colour = texture(texture_diffuse0, fs_in.TexCoords).rgb;
    vec3 ambient = 0.1 * colour;

    vec3 lightDir = normalize(light.pos - fs_in.FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * colour;

    // specular
   
    vec3 viewDir = normalize(view_pos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir ), 0.0), 32.0);
    vec3 specular = vec3(0.2) * spec;

     FragColor = vec4(ambient + diffuse + specular, 1.0);
    //FragColor = vec4(1.0,1.0,1.0,1.0f);

};