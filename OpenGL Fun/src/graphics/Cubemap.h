#pragma once
#include <string>
#include <vector>
#include "../stb_image/stb_image.h"
#include "Cube.h"
#include "GL/glew.h"

class Cubemap
{
private:
	void load(const std::string faces[6]);
	Shader shader;
	GLuint textureID;
	const BufferObject<Vertex> VBO;
	const BufferObject<GLuint>EBO;
	const ArrayObject VAO;
	glm::mat4 ModelMatrix;
public:
	Cubemap(const std::string& path, Shader shader);
	void render();

};

