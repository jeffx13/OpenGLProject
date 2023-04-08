#pragma once
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <vector>
#include "graphics/Shader.h"
#include<glm/gtc/matrix_transform.hpp>

struct Vertex {
    glm::vec3 Pos;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;

    static std::vector<Vertex> genList(float* vertices, int noVertices);

    static void calcTanVectors(std::vector<Vertex>& list, std::vector<unsigned int>& indices);
};
struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> = std::vector<Texture>());
    const std::vector<Vertex>       vertices;
    const std::vector<unsigned int> indices;
	std::vector<Texture>            textures;
    

    glm::mat4 ModelMatrix{ 1.0f };
    glm::vec3 scale{ 1.0f,1.0f,1.0f };
    glm::vec3 world_pos = glm::vec3(0.0f, 0.0f, 0.0f);

    void SetScale(float x_scale = 1.0f, float y_scale = 1.0f, float z_scale = 1.0f);
    void SetScale(glm::vec3 scale);

    void SetTranslation(float x_trans = 0.0f, float y_trans = 0.0f, float z_trans = 0.0f);
    void SetTranslation(glm::vec3 trans);

    void Rotate(float x_rot = 0.0f, float y_rot = 0.0f, float z_rot = 0.0f);
    void Rotate(glm::vec3 rot);

    void SetPosition(float xpos = 0.0f, float ypos = 0.0f, float zpos = 0.0f);
    void SetPosition(glm::vec3 pos);

    void render(Shader& shader, unsigned int instances = 1) const;

    glm::mat4 GetModelMatrix();

    
    void UseDefaultTexture();
    /*void SetMaterial(Material material) {
        this->material = material;
    }*/
private:


    unsigned int VAO, VBO, EBO;

    void Setup();
    void CleanUp() const;

    
};

