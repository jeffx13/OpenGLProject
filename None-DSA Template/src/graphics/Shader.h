#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"



class Shader
{
private:
    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };
    std::string m_FilePath;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string& filePath);
    Shader(const std::string& VertexShaderPath, const std::string& FragmentShaderPath);
    ~Shader();
    unsigned int m_RendererID;
    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void Set1i(const std::string& name, int value);

    void Set1f(const std::string& name, float value);

    void Set4f(const std::string& name, float v0, float v1, float v2, float v3);
    void Set4f(const std::string& name, glm::vec4 v);

    void Set3f(const std::string& name, float v0, float v1, float v2);
    void Set3f(const std::string& name, glm::vec3 v);

    void SetMat4f(const std::string& name, glm::mat4& matrix);
private:

    ShaderProgramSource ParseShader(const std::string filePath);

    std::string ParseFile(std::string path);

    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

    unsigned int CompileShader(unsigned int type, const std::string& source);
    
    unsigned int GetUniformLocation(const std::string& name);
};