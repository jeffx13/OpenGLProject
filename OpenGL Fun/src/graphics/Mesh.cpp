#include "Mesh.h"
#include <iostream>
#include <utility>
#include "../res/stb_image/stb_image.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : VBO(GL_ARRAY_BUFFER, vertices), EBO(GL_ELEMENT_ARRAY_BUFFER, indices),VAO(VBO,EBO),
      vertices(vertices), indices(indices), textures(textures), Transformable()
{}
void Mesh::render(Shader& shader, unsigned int instances)
{
    GLuint nDiffuse = 0;
    GLuint nSpecular = 0;
    GLuint nNormal = 0;
    GLuint nHeight = 0;
    bool normalmap = false;
    glBindVertexArray(VAO.ID);
    shader.bind();
    shader.set("model", Transformable::getModelMatrix());
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        std::string number;
        std::string name = textures[i].type;
        if (name == "diffuse"){ number = std::to_string(nDiffuse++); }
        else if (name == "specular"){ number = std::to_string(nSpecular++); }
        else if (name == "normal"){ number = std::to_string(nNormal++);normalmap = true; }
        else if (name == "height"){ number = std::to_string(nHeight++); }
        glBindTextureUnit(i, textures[i].id);
        shader.set((name + number).c_str(), i);
    }
    if (!normalmap) { shader.set("b_normal_map", -100); }else{ shader.set("b_normal_map", 100); }
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
    this->textures.push_back(Texture{ 100,"diffuse" ,"res/textures/brick.png" });
}
