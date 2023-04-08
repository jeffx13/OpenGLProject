#pragma once
#include <string>
#include <vector>
#include <stb_image/stb_image.h>

#include "Cube.h"
#include "Mesh.h"
#include "graphics/Renderer.h"
#include "GL/glew.h"

class Cubemap
{
public:
	Cubemap(const std::string& path);
	void render(Shader& shader, glm::mat4& view, glm::mat4& projection);
private:
	void load(const std::string faces[6]);
	unsigned int textureID;
    unsigned int VAO, VBO, EBO;
    glm::mat4 ModelMatrix;
};

