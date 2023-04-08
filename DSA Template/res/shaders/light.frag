#version 450 core

layout(location = 0) out vec4 FragColour;

struct Pointlight{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 colour;
};
uniform Pointlight pointlight;

void main()
{
    FragColour = vec4(pointlight.colour,1.0f);
    
};