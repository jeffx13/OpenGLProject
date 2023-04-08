#include "VertexBuffer.h"
#include "Renderer.h"
#include "Mesh.h"
VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices)
{
    GLCall(glGenBuffers(1, &m_RendererID)); // Generate a single buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // Select the buffer to be drawn
    GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW)); // Add the data to the buffer
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));  
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
