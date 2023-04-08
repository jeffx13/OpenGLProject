#pragma once
#include <iostream>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

#include "Scene.h"

template<typename T>
class BufferObject
{
public:
    BufferObject(GLenum type, const std::vector<T>& data):type(type)
    {
        glCreateBuffers(1, &this->ID);
        setData(data);
        Scene::registerBuffer(ID);
    };
    BufferObject(GLenum type) :type(type){glCreateBuffers(1, &this->ID);Scene::registerBuffer(ID);}
    void setData(const std::vector<T>& data);
    void setSubData(const std::vector<T>& data);
    GLuint getCount() const { return count; }
    GLuint ID;
private:
    GLenum type;
    GLuint count;
    
};


template <typename T>
void BufferObject<T>::setData(const std::vector<T>& data)
{
    glNamedBufferData(ID, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
    count = data.size();
}


class UBO
{
public:
    enum Type
    {
        SCALAR = 4,
        VEC3 = 16,
        VEC4 = VEC3,
        MAT3 = VEC3 * 3,
        MAT4 = VEC4 * 4
    };
    UBO(GLuint bindingPoint);
    UBO();
    UBO(GLuint bindingPoint, std::vector<Type> layout);
    void setBindingPoint(GLuint bindingpoint);
    template<typename T>
    void setLayout(std::vector<T> layout);
    template<>
    void setLayout<Type>(std::vector<Type> layout);
    template<>
    void setLayout<GLuint>(std::vector<GLuint> layout);

   template <typename T>
	void setSubData(GLuint offset, T data);
    template <class T>
    void setSubData(GLuint offset, GLuint size, T data);

    void setSize(GLuint size) { this->size = size; glNamedBufferData(ID, size, nullptr, GL_STATIC_DRAW); }
    GLuint ID;
private:
	GLuint calBufferOffset(GLuint offset);
    GLuint size;
    GLenum type;
    std::vector<GLuint> layout;
};

template <typename T>
void UBO::setLayout(std::vector<T> layout)
{
}

template <class T>
void UBO::setSubData(GLuint offset, GLuint size, T data)
{
    glNamedBufferSubData(ID, offset, size, &data);
    
   /* void* ptr = glMapNamedBufferRange(ID, offset, size, GL_MAP_WRITE_BIT| GL_MAP_INVALIDATE_BUFFER_BIT| GL_MAP_UNSYNCHRONIZED_BIT);
    memcpy(ptr, &data, size);
    glUnmapNamedBuffer(ID);*/
}
template <typename T>
void UBO::setSubData(GLuint offset, T data)
{
    GLuint dataSize = sizeof(T);
    switch (sizeof(T))
    {
    case(12):dataSize = 16; break;
    case(36):dataSize = 48; break;
    }
    assert(dataSize == layout[offset]);
    glNamedBufferSubData(ID, calBufferOffset(offset), dataSize, &data);
}



class ArrayObject
{
public:
    ArrayObject( const BufferObject<struct Vertex>& VBO, const BufferObject<GLuint>& EBO);
    ArrayObject() { glCreateVertexArrays(1, &ID);Scene::registerVertexArray(ID);}

    void bind() const{ glBindVertexArray(ID); }
    static void unbind(){ glBindVertexArray(0); }
    void addVertexBuffer(const BufferObject<Vertex>& VBO);
    void addIndexBuffer(const BufferObject<GLuint>& EBO);
    GLuint getIndicesCount() const { return EBO->getCount(); }
    GLuint ID;
private:
    const BufferObject<Vertex>* VBO{ nullptr };
    const BufferObject<GLuint>* EBO{ nullptr };
};

