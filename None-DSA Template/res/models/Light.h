#pragma once
#include "Mesh.h"

struct Light : public Mesh
{
	Light(std::vector<Vertex> Vertices,
		std::vector<GLuint> Indices,
		glm::vec3 colour = {1.0f,1.0f,1.0f},
		glm::vec3 ambient = { 1.0f,1.0f,1.0f },
		glm::vec3 specular = { 1.0f,1.0f,1.0f },
		glm::vec3 diffuse = { 1.0f,1.0f,1.0f })
		:Mesh(Vertices, Indices), colour(colour), ambient(ambient), specular(specular), diffuse(diffuse){};

	glm::vec3 colour;
	glm::vec3 ambient;
	glm::vec3 specular;
	glm::vec3 diffuse;
	
	
};

