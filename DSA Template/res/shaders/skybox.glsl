#shader vertex
#version 450 core
layout(location = 0) in vec3 aPos;

layout(std140, binding = 0) uniform matrices
{
    mat4 view;
    mat4 projection;
};

out vec3 TexCoords;

uniform mat4 model;


void main()
{
    TexCoords = aPos;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment
#version 450 core
layout(location = 0) out vec4 FragColour;

in vec3 TexCoords;
uniform samplerCube skybox;

void main()
{
    FragColour = texture(skybox, TexCoords);
};

