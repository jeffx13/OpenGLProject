#include "GLmemory.h"
#include "graphics/Mesh.h"
#include "Scene.h"


UBO::UBO(GLuint bindingPoint)
{
	glCreateBuffers(1, &ID);
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ID);
	Scene::registerBuffer(ID);
}

UBO::UBO()
{
	
}

UBO::UBO(GLuint bindingPoint, std::vector<Type> layout): UBO(bindingPoint)
{
	setLayout(layout);
	Scene::registerBuffer(ID);
}

void UBO::setBindingPoint(GLuint bindingPoint)
{
	glCreateBuffers(1, &ID);
	Scene::registerBuffer(ID);
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ID);
}

template <>
void UBO::setLayout<unsigned>(std::vector<GLuint> layout)
{
	this->layout = layout;
	for (const auto type : this->layout)
	{
		this->size += type;
	}
	glNamedBufferData(ID, size, NULL, GL_STATIC_DRAW);
}

template <>
void UBO::setLayout<UBO::Type>(std::vector<Type> layout)
{
	std::copy(layout.begin(), layout.end(),
		std::back_inserter(this->layout));
	for (const auto type : this->layout)
	{
		this->size +=(GLuint)type;
	}
	glNamedBufferData(ID, size, NULL, GL_STATIC_DRAW);
}


GLuint UBO::calBufferOffset(GLuint offset)
{
	GLuint bufferOffset{ 0 };
	for (size_t i{ 0 };i < offset;i++)
	{
		bufferOffset += static_cast<GLuint>(layout[i]);
	}
	return bufferOffset;
}


ArrayObject::ArrayObject(const BufferObject<Vertex>& VBO, const BufferObject<GLuint>& EBO)
	:VBO(&VBO), EBO(&EBO)
{
	Scene::registerVertexArray(ID);
	glCreateVertexArrays(1, &ID);
	addVertexBuffer(VBO);
	addIndexBuffer(EBO);

	glEnableVertexArrayAttrib(ID, 0);
	glEnableVertexArrayAttrib(ID, 1);
	glEnableVertexArrayAttrib(ID, 2);
	glEnableVertexArrayAttrib(ID, 3);
	glEnableVertexArrayAttrib(ID, 4);

	glVertexArrayAttribFormat(ID, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Pos));
	glVertexArrayAttribFormat(ID, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Normal));
	glVertexArrayAttribFormat(ID, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, TexCoords));
	glVertexArrayAttribFormat(ID, 3, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Tangent));
	glVertexArrayAttribFormat(ID, 4, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Bitangent));

	glVertexArrayAttribBinding(ID, 0, 0);
	glVertexArrayAttribBinding(ID, 1, 0);
	glVertexArrayAttribBinding(ID, 2, 0);
	glVertexArrayAttribBinding(ID, 3, 0);
	glVertexArrayAttribBinding(ID, 4, 0);
}

void ArrayObject::addVertexBuffer(const BufferObject<Vertex>& VBO)
{
	this->VBO = &VBO;
	glVertexArrayVertexBuffer(ID, 0, VBO.ID, 0, sizeof(Vertex));
}

void ArrayObject::addIndexBuffer(const BufferObject<GLuint>& EBO)
{
	this->EBO = &EBO;
	glVertexArrayElementBuffer(ID, EBO.ID);
}