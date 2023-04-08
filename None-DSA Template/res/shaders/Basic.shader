#shader vertex
#version 330 core;

layout(location = 0) in vec3 a_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = vec4(a_pos,1.0);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

void main()
{
    
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
};