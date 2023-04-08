#include "Light.h"
#define light name + "[" + std::to_string(idx) + "]"
void Lamp::render(Shader& shader, GLuint idx, unsigned int instances)
{
	shader.bind();

	switch (type)
	{
	case DIRECTIONAL:
		this->shader.set("colour", dirlight.colour);
		shader.set(name + "s[" + std::to_string(idx) + "]" + ".diffuse", dirlight.diffuse);
		shader.set(name + "s[" + std::to_string(idx) + "]" + ".ambient", dirlight.ambient);
		shader.set(name + "s[" + std::to_string(idx) + "]" + ".specular", dirlight.specular);
		shader.set(name + "s[" + std::to_string(idx) + "]" + ".colour", dirlight.colour);

		break;
	case POINT:
		pointlight.position = modelPos;
		this->shader.set("colour", pointlight.colour);
		shader.set<glm::vec3>(name + "s[" + std::to_string(idx) + "]" + ".diffuse", pointlight.diffuse);
		shader.set<glm::vec3>(name + "s[" + std::to_string(idx) + "]" + ".ambient", pointlight.ambient);
		shader.set<glm::vec3>(name + "s[" + std::to_string(idx) + "]" + ".specular", pointlight.specular);
		shader.set<glm::vec3>(name + "s[" + std::to_string(idx) + "]" + ".colour", pointlight.colour);
		shader.set<glm::vec3>(name + "s[" + std::to_string(idx) + "]" + ".position", pointlight.position);
		break;
	case SPOT:
		spotlight.position = modelPos;
		shader.set("colour", spotlight.colour);
		shader.set(name + "s[" + std::to_string(idx) + "]" + ".diffuse", spotlight.diffuse);
		shader.set(name + "s[" + std::to_string(idx) + "]" + ".ambient", spotlight.ambient);
		shader.set(name + "s[" + std::to_string(idx) + "]" + ".specular", spotlight.specular);
		shader.set(name + "s[" + std::to_string(idx) + "]" + ".colour", spotlight.colour);
		shader.set(name + "s[" + std::to_string(idx) + "]" + ".position", spotlight.position);
		shader.set(name + "s[" + std::to_string(idx) + "]" + ".innerCutOff", spotlight.innerCutOff);
		shader.set(name + "s[" + std::to_string(idx) + "]" + ".outerCutOff", spotlight.outerCutOff);
		break;
	}

	Model::render(this->shader, instances);
}