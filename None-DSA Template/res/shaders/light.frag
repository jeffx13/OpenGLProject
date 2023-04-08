#version 330 core

layout(location = 0) out vec4 FragColour;
uniform vec3 light_colour;

void main()
{
    FragColour = vec4(light_colour,1.0f);
    
};