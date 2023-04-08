#include "Shader.h"
#include <stdio.h>
#include <fstream>


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Shader.h"
#include "Scene.h"

Shader::Shader(const std::string & filePath)
    : m_FilePath(filePath), ID(0)
{
    ShaderProgramSource source = ParseShader(filePath);
    ID = CreateShader(source.VertexSource, source.FragmentSource);
    name = filePath;
    
}

Shader::Shader(const std::string& VertexShaderPath, const std::string& FragmentShaderPath)
{
    std::string vs_source;
    std::string fs_source;
    vs_source = ParseFile(VertexShaderPath);
    fs_source = ParseFile(FragmentShaderPath);
    ID = CreateShader(vs_source, fs_source);
    Scene::registerShader(ID);
}

std::string Shader::ParseFile(const std::string filePath) {
    std::stringstream ss;
    std::fstream stream(filePath);
    std::string line;
    while (getline(stream, line)) {
        ss << line << '\n';
    }
    return ss.str();
};

Shader::ShaderProgramSource Shader::ParseShader(const std::string filePath) const
{
    std::ifstream stream(filePath);
    enum class Shadertype
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2]; // 2 for vertex and fragment shaders
    Shadertype type = Shadertype::NONE;

    while (getline(stream, line))
    {
        // Set the type if #shader is found
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = Shadertype::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = Shadertype::FRAGMENT;
        }
        else // Add the line to the source
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type); // Create the shader
    const char* src = source.c_str(); // Return the pointer of the first character of the source
    GLCall(glShaderSource(id, 1, &src, nullptr)); // Specify the shader source code
    GLCall(glCompileShader(id));

    // Error handling
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result)); // Returns the compile status parameter
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char)); // Allocate this on the stack dynamically because 'char message[length]' is not allowed
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader:" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram(); // Create a shader program to attach shader to
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // Attach both shaders to the program
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));

    GLCall(glLinkProgram(program)); // Link the program so the shaders are used
    GLCall(glValidateProgram(program)); // Check if the program can be executed

                                        // The shaders are linked to the progam, so the shaders can be deleted
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::bind() const
{
    glUseProgram(ID);
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

template <>
void Shader::set<int>(const std::string& name, GLint value)
{
    bind();
    glUniform1i(GetUniformLocation(name), value);
}


template <>
void Shader::set<float>(const std::string& name, GLfloat value)
{
    glUniform1f(GetUniformLocation(name), value);
}

template <>
void Shader::set<glm::vec<3, float, glm::defaultp>>(const std::string& name, glm::vec3 v)
{
    set(name, v.x, v.y, v.z);
}

template <>
void Shader::set<glm::vec<4, float, glm::defaultp>>(const std::string& name, glm::vec4 v)
{
    set(name, v.x, v.y, v.z, v.w);
}

template <>
void Shader::set<glm::mat<4, 4, float, glm::defaultp>>(const std::string& name, glm::mat4 matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

template <>
void Shader::set<float>(const std::string& name, GLfloat v1, GLfloat v2, GLfloat v3)
{
    glUniform3f(GetUniformLocation(name),v1, v2, v3);
}

template <>
void Shader::set<float>(const std::string& name, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4)
{
    glUniform4f(GetUniformLocation(name), v1, v2, v3, v4);
}


unsigned int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist! in " << m_FilePath << std::endl;
    
    m_UniformLocationCache[name] = location;
    return location;
}
