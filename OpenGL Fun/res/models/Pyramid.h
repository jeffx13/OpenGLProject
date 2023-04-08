#pragma once
#include <vector>
#include "Material.h"
#include "graphics/Mesh.h"
struct Pyramid
{
  
	inline static const std::vector<Vertex> Vertices =
	{ 
		Vertex{ {-0.5f, 0.0f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}}, // Bottom side
		Vertex{ {-0.5f, 0.0f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 5.0f}}, // Bottom side
		Vertex{ { 0.5f, 0.0f, -0.5f}, {0.0f, -1.0f, 0.0f}, {5.0f, 5.0f}}, // Bottom side
		Vertex{ { 0.5f, 0.0f,  0.5f}, {0.0f, -1.0f, 0.0f}, {5.0f, 0.0f}}, //  Bottom side
		
		Vertex{ {-0.5f, 0.0f,  0.5f}, {-0.8f,  0.5f, 0.0f}, {0.0f, 0.0f}}, // Left Side
		Vertex{ {-0.5f, 0.0f, -0.5f}, {-0.8f,  0.5f, 0.0f}, {5.0f, 0.0f}}, // Left Side
		Vertex{ { 0.0f, 0.8f,  0.0f}, {-0.8f,  0.5f, 0.0f}, {2.5f, 5.0f}}, // Left Side
		
		Vertex{ {-0.5f, 0.0f, -0.5f}, {0.0f,  0.5f, -0.8f}, {5.0f, 0.0f}}, // Non-facing side
		Vertex{ { 0.5f, 0.0f, -0.5f}, {0.0f,  0.5f, -0.8f}, {0.0f, 0.0f}}, // Non-facing side
		Vertex{ { 0.0f, 0.8f,  0.0f}, {0.0f,  0.5f, -0.8f}, {2.5f, 5.0f}}, // Non- facing side
		
		Vertex{ { 0.5f, 0.0f, -0.5f}, {0.8f,  0.5f, 0.0f}, {0.0f, 0.0f}}, // Right side
		Vertex{ { 0.5f, 0.0f,  0.5f}, {0.8f,  0.5f, 0.0f}, {5.0f, 0.0f}}, // Right side
		Vertex{ { 0.0f, 0.8f,  0.0f}, {0.8f,  0.5f, 0.0f}, {2.5f, 5.0f}}, // Right side
		                             
		Vertex{ { 0.5f, 0.0f,  0.5f}, {0.0f,  0.5f, 0.8f}, {5.0f, 0.0f}}, // Facing side
		Vertex{ {-0.5f, 0.0f,  0.5f}, {0.0f,  0.5f, 0.8f}, {0.0f, 0.0f}}, // Facing side
		Vertex{ { 0.0f, 0.8f,  0.0f}, {0.0f,  0.5f, 0.8f}, {2.5f, 5.0f}}, // Facing side
	};
	inline static const std::vector<GLuint> Indices =
	{
		0, 1, 2, // Bottom side
		0, 2, 3, // Bottom side
		4, 6, 5, // Left side
		7, 9, 8, // Non-facing side
		10, 12, 11, // Right side
		13, 15, 14 // Facing side
	};

	inline static const std::vector<Vertex> TriangleVertices =
	{
		Vertex({0.5,-0.5f,0.0f}),
		Vertex({-0.5,-0.5f,0.0f}),
		Vertex({0.0,0.5f,0.0f}),
	};

	Material::Material material;
	void SetMaterial(Material::Material material) {
		this->material = material;
	}
};

