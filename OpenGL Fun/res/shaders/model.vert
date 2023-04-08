#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

layout (std140,binding = 0) uniform matrices
{
    mat4 view;
    mat4 projection;
};

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

uniform mat4 model;

void main()
{
    vs_out.FragPos = vec3( model * vec4(aPos, 1.0));   
    vs_out.TexCoords = aTexCoords;
    
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    vs_out.Normal = N;
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    //vs_out.TangentLightPos = TBN * lightPos;
    //vs_out.TangentViewPos  = TBN * viewPos;
    //vs_out.TangentFragPos  = TBN * vs_out.FragPos;
    
    //mat4 translate = mat4(1.0, 0.0, 0.0, 0.0,  0.0, 1.0, 0.0, 0.0,  0.0, 0.0, 1.0, 0.0,  gl_InstanceID*0.1f, -0.0, -0, 1.0);
    gl_Position = projection * view *model * vec4(aPos, 1.0);
};
