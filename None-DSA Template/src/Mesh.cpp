#include "Mesh.h"
#include <iostream>
#include <utility>
#include <vendor/stb_image/stb_image.h>

std::vector<Vertex> Vertex::genList(float* vertices, int noVertices)
{
	std::vector<Vertex> Vertices(noVertices);

    int stride = sizeof(Vertex)/sizeof(float);

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
    : vertices(std::move(vertices)),
      indices(std::move(indices)), textures(textures)
{
    Setup();
}

void Mesh::render(Shader& shader, unsigned int instances) const
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        shader.Set1i((name + number).c_str(), i);
        //glUniform1i(glGetUniformLocation(shader.m_RendererID, (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // draw mesh
    glBindVertexArray(VAO);
    if(instances>1)
    {
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0, instances);
    }else
    {
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    }
    
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::Setup()
{
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    
}

void Mesh::CleanUp() const
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::SetScale(float x_scale, float y_scale, float z_scale)
{
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(x_scale, y_scale, z_scale));
	scale = glm::vec3(x_scale, y_scale, z_scale);
}

void Mesh::SetScale(glm::vec3 scale)
{
	SetScale(scale.x, scale.y, scale.z);
}

void Mesh::SetTranslation(float x_trans, float y_trans, float z_trans)
{
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(x_trans, y_trans, z_trans));
	world_pos += glm::vec3(x_trans, y_trans, z_trans);
}

void Mesh::SetTranslation(glm::vec3 trans)
{
	SetTranslation(trans.x, trans.y, trans.z);
}

void Mesh::Rotate(float x_rot, float y_rot, float z_rot)
{
	if (x_rot != 0) {
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(x_rot), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (y_rot != 0) {
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(y_rot), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (z_rot != 0) {
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(z_rot), glm::vec3(0.0f, 0.0f, 1.0f));
	}
}

void Mesh::Rotate(glm::vec3 rot)
{
	Rotate(rot.x, rot.y, rot.x);
}

void Mesh::SetPosition(float xpos, float ypos, float zpos)
{
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
	world_pos = glm::vec3(xpos, ypos, zpos);
}

void Mesh::SetPosition(glm::vec3 pos)
{
	SetPosition(pos.x, pos.y, pos.z);
}

glm::mat4 Mesh::GetModelMatrix()
{
	return ModelMatrix;
}

void Mesh::UseDefaultTexture()
{
    this->textures.push_back(Texture{ 100,"texture_diffuse" ,"res/models/default_texture.jpg" });
}
