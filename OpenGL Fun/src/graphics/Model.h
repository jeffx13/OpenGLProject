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
#include "Transformable.h"
#include "graphics/Shader.h"

class Model: public Transformable
{
public:
	Model(const std::string& path);
	Model(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
	void addMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
	Model(std::vector<Vertex> vertices,
	      std::vector<unsigned int> indices,
	      std::vector<Texture> = std::vector<Texture>());

	void scale(float x_scale = 1.0f, float y_scale = 1.0f, float z_scale = 1.0f) override;
	void scale(glm::vec3 vec) override;

	void translate(float x_trans = 0.0f, float y_trans = 0.0f, float z_trans = 0.0f) override;
	void translate(glm::vec3 trans) override;

	void rotate(float x_rot = 0.0f, float y_rot = 0.0f, float z_rot = 0.0f) override;
	void rotate(glm::vec3 rot) override;

	void setPosition(float xpos = 0.0f, float ypos = 0.0f, float zpos = 0.0f) override;
	void setPosition(glm::vec3 pos) override;


	void render(Shader& shader, unsigned int instances = 1);
private:
	std::vector<Mesh> meshes;
	void load(const std::string& path);
	std::string directory;
	
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> textures_loaded;
	std::vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type, std::string type_name);
	static inline std::string defautlDirectory{ NULL };
};

