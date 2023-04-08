#pragma once
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <vector>
#include "graphics/Shader.h"
#include<glm/gtc/matrix_transform.hpp>

#include "Transformable.h"
#include "GLmemory.h"

struct Vertex {
    glm::vec3 Pos;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};
struct Texture
{
    GLuint id;
    std::string type;
    std::string path;
    
};

class Mesh: public Transformable
{
protected:
    const BufferObject<Vertex> VBO;
    const BufferObject<GLuint> EBO;
    ArrayObject VAO;
    const std::vector<Vertex>       vertices;
    const std::vector<GLuint> indices;
    std::vector<Texture>            textures;
    void CleanUp() const;
public:
    Mesh(std::vector<Vertex> vertices,
        std::vector<GLuint> indices,
        std::vector<Texture> = std::vector<Texture>());

    void render(Shader& shader, unsigned int instances = 1);
    void UseDefaultTexture();
};

