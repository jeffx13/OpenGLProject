#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include "GL/glew.h"
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


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
    std::string name;
public:
    Shader(const std::string& filePath);
    Shader(const std::string& VertexShaderPath, const std::string& FragmentShaderPath);

    GLuint ID;
    void bind() const;
    void unbind() const;

    template<typename T>
    void set(const std::string& name, T value);

    template<>
    void set<GLint>(const std::string& name, GLint value);

    template<>
    void set<GLfloat>(const std::string& name, GLfloat value);

    template<>
    void set<glm::vec3>(const std::string& name, glm::vec3 v);

    template<>
    void set<glm::vec4>(const std::string& name, glm::vec4 v);

    template<>
    void set<glm::mat4>(const std::string& name, glm::mat4 matrix);

    template<typename T>
    void set(const std::string& name, T x, T y, T z);
    template<>
    void set<GLfloat>(const std::string& name, GLfloat v1, GLfloat v2, GLfloat v3);

    template<typename T>
    void set(const std::string& name, T x, T y, T z, T w);
    template<>
    void set<GLfloat>(const std::string& name, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4);

private:

    ShaderProgramSource ParseShader(const std::string filePath) const;

    std::string ParseFile(std::string path);

    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

    unsigned int CompileShader(unsigned int type, const std::string& source);
    
    unsigned int GetUniformLocation(const std::string& name);
};

template <typename T>
void Shader::set(const std::string& name, T value)
{
}

template <typename T>
void Shader::set(const std::string& name, T x, T y, T z)
{
}

template <typename T>
void Shader::set(const std::string& name, T x, T y, T z, T w)
{
}
