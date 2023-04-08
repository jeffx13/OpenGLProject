#include "Mesh.h"
#include <iostream>
#include <utility>
#include <vendor/stb_image/stb_image.h>

std::vector<Vertex> Vertex::genList(float* vertices, int noVertices)
{
    std::vector<Vertex> Vertices(noVertices);

    int stride = sizeof(Vertex) / sizeof(float);

    for (int i = 0; i < noVertices; i++) {
        Vertices[i].Pos = glm::vec3(
            vertices[i * stride + i],
            vertices[i * stride + i],
            vertices[i * stride + i]
        );
        Vertices[i].Normal = glm::vec3(
            vertices[i * stride + i],
            vertices[i * stride + i],
            vertices[i * stride + i]
        );
        Vertices[i].TexCoords = glm::vec2(
            vertices[i * stride + i],
            vertices[i * stride + i]
        );

        Vertices[i].Tangent = glm::vec3(
            vertices[i * stride + i],
            vertices[i * stride + i],
            vertices[i * stride + i]
        );
        Vertices[i].Bitangent = glm::vec3(
            vertices[i * stride + i],
            vertices[i * stride + i],
            vertices[i * stride + i]
        );
    }
    return Vertices;
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : VBO(GL_ARRAY_BUFFER, vertices), EBO(GL_ELEMENT_ARRAY_BUFFER, indices),VAO(VBO,EBO),
      vertices(vertices), indices(indices), textures(textures), Transformable()
{}
void Mesh::render(Shader& shader, unsigned int instances)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    glBindVertexArray(VAO.ID);
    shader.bind();
    shader.set("model", Transformable::getModelMatrix());
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        std::string number;
        std::string name = textures[i].type;
        if (name == "diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        glBindTextureUnit(i, textures[i].id);
        shader.set((name + number).c_str(), i);
    }

    glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, instances);
}

void Mesh::CleanUp() const
{
    glDeleteVertexArrays(1, &VAO.ID);
    glDeleteBuffers(1, &VBO.ID);
    glDeleteBuffers(1, &EBO.ID);
}


void Mesh::UseDefaultTexture()
{
    this->textures.push_back(Texture{ 100,"texture_diffuse" ,"res/models/default_texture.jpg" });
}
