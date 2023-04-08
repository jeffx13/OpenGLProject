#pragma once
#include <GL/glew.h>
#include "graphics/VertexBuffer.h"
#include "graphics/VertexBufferLayout.h"
#include "graphics/VertexArray.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Shader.h"
#include <iostream>
#include "Model.h"

#define ASSERT(x) if (!(x)) __debugbreak(); // Break debugging if x returns false
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__)); // Wrap a function with an error boundary

/**
Clear all (unrelated) previous errors.
*/
void GLClearError();

/**
Check for an error and log the error to the console.

@param function The function where the error happend
@param file The file where the error happend
@param line The line number where the error happend
@return Whether there was an error
*/
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Clear() const;
    void Render(Model model, Shader& shader) const;
    void Render(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};