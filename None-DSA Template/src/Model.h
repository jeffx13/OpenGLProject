#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "Mesh.h"
#include "graphics/Shader.h"

class Model
{
public:
	std::vector<Mesh> meshes;
	Model(const std::string& path);
	void load(const std::string& path);
	void render(Shader& shader, unsigned int instances=1) const;
	std::string directory;
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> textures_loaded;
	std::vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type, std::string type_name);
	

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

	glm::mat4 GetModelMatrix() const;
};

