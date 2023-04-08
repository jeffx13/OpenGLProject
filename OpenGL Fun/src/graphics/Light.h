#pragma once
#include "graphics/Model.h"
#include <memory>

#include "graphics/Shader.h"


struct Dirlight
{
	glm::vec3 diffuse{};
	glm::vec3 ambient{};
	glm::vec3 specular{};
	glm::vec3 colour{};
	glm::vec3 direction{};
};

struct Pointlight
{
	glm::vec3 position{ 1.0f, 1.0f, 1.0f };
	glm::vec3 diffuse { 0.5f, 0.5f, 0.5f };
	glm::vec3 ambient { 1.0f, 1.0f, 1.0f };
	glm::vec3 specular{ 0.2f, 0.2f, 0.2f };
	glm::vec3 colour  { 1.0f, 1.0f, 1.0f };
};

struct Spotlight
{
	glm::vec3 diffuse;
	glm::vec3 ambient;
	glm::vec3 specular;
	glm::vec3 colour;

	glm::vec3 position;
	glm::vec3 direction;
	float innerCutOff;
	float outerCutOff;
};

class Lamp : public Model
{
public:
	enum Type {
		DIRECTIONAL,
		POINT,
		SPOT
	};

	Lamp(std::vector<Vertex> vertices,
		std::vector<GLuint> indices,
		Spotlight spotlight,
		Shader shader)
		:Model(vertices, indices), type(SPOT), name("spotlight"), spotlight(spotlight), shader(shader)
	{
		Model::setPosition(spotlight.position);
	}

	Lamp(std::vector<Vertex> vertices,
		std::vector<GLuint> indices,
		Pointlight pointlight,
		Shader shader)
		:Model(vertices, indices), type(POINT), name("pointlight"), pointlight(pointlight), shader(shader)
	{
		Model::setPosition(pointlight.position);
	}

	Lamp(std::vector<Vertex> vertices,
		std::vector<GLuint> indices,
		Dirlight dirlight,
		Shader shader)
		:Model(vertices, indices), type(DIRECTIONAL), name("dirlight"), dirlight(dirlight), shader(shader) {}

	Type type;
	std::string name;
	Dirlight dirlight{};
	Pointlight pointlight{};
	Spotlight spotlight{};
	Shader shader;
	void render(Shader& shader, GLuint idx, unsigned int instances = 1);

	
};

