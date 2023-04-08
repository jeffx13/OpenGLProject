#pragma once
#include "graphics/Mesh.h"
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
	glm::vec3 position{};
	glm::vec3 diffuse{ 0.5f,0.5f,0.5f };
	glm::vec3 ambient{ 0.5f,0.5f,0.5f };
	glm::vec3 specular{ 0.5f,0.5f,0.5f };
	glm::vec3 colour{ 0.5f,0.5f,0.5f };

	
};

struct Spotlight
{
	glm::vec3 diffuse{};
	glm::vec3 ambient{};
	glm::vec3 specular{};
	glm::vec3 colour{};

	glm::vec3 position{};
	glm::vec3 direction{};
	float innerCutOff{};
	float outerCutOff{};
};

class Lamp : public Model
{
public:
	enum Type
	{
		DIRECTIONAL,
		POINT,
		SPOT
	};
	Lamp(std::vector<Vertex> vertices,
		std::vector<GLuint> indices,
		glm::vec3 position,
		glm::vec3 direction,
		float innerCutOff,
		float outerCutOff,
		glm::vec3 diffuse = { 0.5f,0.5f,0.5f },
		glm::vec3 ambient = { 0.5f,0.5f,0.5f },
		glm::vec3 specular = { 0.5f,0.5f,0.5f },
		glm::vec3 colour = { 1.0f,1.0f,1.0f })
	:Model(vertices, indices), type(SPOT), name("spotlight"), ambient(ambient),
	specular(specular), diffuse(diffuse), colour(colour), position(position),
	direction(direction), innerCutOff(innerCutOff), outerCutOff(outerCutOff) {}

	Lamp(std::vector<Vertex> vertices,
		std::vector<GLuint> indices,
		Type type,
		glm::vec3 vec,
		glm::vec3 diffuse = { 0.5f, 0.5f, 0.5f },
		glm::vec3 ambient = { 0.5f, 0.5f, 0.5f },
		glm::vec3 specular = { 0.5f, 0.5f, 0.5f },
		glm::vec3 colour = { 1.0f,1.0f,1.0f })
		:Model(vertices, indices), type(type), ambient(ambient), specular(specular), diffuse(diffuse), colour(colour)
	{
		switch (type)
		{
		case DIRECTIONAL:name = "dirlight"; direction = vec; break;
		case POINT:name = "pointlight"; position = vec; break;
		}
		Model::setPosition(position);
	}

	Type type{};
	std::string name;
	glm::vec3 ambient;
	glm::vec3 specular;
	glm::vec3 diffuse;
	glm::vec3 colour;
	glm::vec3 position{};
	glm::vec3 direction{};
	float innerCutOff{};
	float outerCutOff{};

	void render(Shader& selfshader, Shader& shader, unsigned int instances = 1)
	{
		Model::render(selfshader,instances);
		selfshader.set("pointlight.colour", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.bind();
		shader.set(name + ".ambient", ambient);
		shader.set(name + ".diffuse", diffuse);
		shader.set(name + ".specular", specular);
		//shader.set(name + ".colour", colour);

		switch (type)
		{
		case DIRECTIONAL:
			shader.set(name + ".direction", direction);break;
		case POINT:
			shader.set(name + ".position", Model::modelPos);break;
		case SPOT:
			shader.set(name + ".position", Model::modelPos);
			shader.set(name + ".direction", direction);
			shader.set(name + ".innerCutOff", innerCutOff);
			shader.set(name + ".outerCutOff", outerCutOff);
			break;
		}
	}
};

