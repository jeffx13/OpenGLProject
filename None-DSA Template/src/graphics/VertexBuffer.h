#pragma once
#include <GL/glew.h>
#include <vector>
#include "glm/glm.hpp"


class VertexBuffer
{
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const std::vector<struct Vertex>& vertices);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};