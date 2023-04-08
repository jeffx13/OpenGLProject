#shader vertex
#version 450 core

layout(location = 0) in vec3 aPos;

layout(std140, binding = 0) uniform matrices
{
    mat4 view;
    mat4 projection;
};

uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
};



#shader fragment
#version 450 core

layout(location = 0) out vec4 FragColour;
uniform vec3 colour;
void main()
{
    FragColour = vec4(colour, 1.0f);
};
