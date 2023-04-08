#version 450 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_colour;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec2 a_texcoord;
layout(location = 4) in vec2 tangent;

out VS_OUT {
    vec2 TexCoords;
    vec3 VertexColour;
    vec3 Normal;
    vec3 FragPos;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{

   gl_Position = projection * view * model * vec4(a_pos,1.0f);
   vs_out.TexCoords = a_texcoord;
   vs_out.VertexColour = a_colour;
   vs_out.FragPos = a_pos;
   vs_out.Normal = mat3(transpose(inverse(model))) * a_normal;
};
