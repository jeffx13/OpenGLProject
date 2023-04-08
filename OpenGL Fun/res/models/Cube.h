#pragma once
#include <vector>
#include "Material.h"
#include "graphics/Mesh.h"
struct Cube
{
    inline static const std::vector<Vertex> Vertices = {
        //Position           //Colour            //Normal                //Texture
Vertex{{ 0.5f, 0.5f, 0.5f}, { 1.0f,  1.0f,  1.0f},  {1.0f, 1.0f},  {0.0f,0.0f,0.0f}}, // 0 top right front
Vertex{{-0.5f, 0.5f, 0.5f}, {-1.0f,  1.0f,  1.0f},  {0.0f, 1.0f},  {0.0f,0.0f,0.0f}}, // 1 top left front
Vertex{{ 0.5f,-0.5f, 0.5f}, { 1.0f, -1.0f,  1.0f},  {1.0f, 0.0f},  {0.0f,0.0f,0.0f}}, // 2 bottom right front
Vertex{{-0.5f,-0.5f, 0.5f}, {-1.0f, -1.0f,  1.0f},  {0.0f, 0.0f},  {0.0f,0.0f,0.0f}}, // 3 bottom left front

Vertex{{ 0.5f, 0.5f,-0.5f}, { 1.0f,  1.0f, -1.0f},  {1.0f, 0.0f},  {0.0f,0.0f,0.0f}}, // 4 top right back
Vertex{{-0.5f, 0.5f,-0.5f}, {-1.0f,  1.0f, -1.0f},  {0.0f, 1.0f},  {0.0f,0.0f,0.0f}}, // 5 top left back
Vertex{{ 0.5f,-0.5f,-0.5f}, { 1.0f, -1.0f, -1.0f},  {1.0f, 0.0f},  {0.0f,0.0f,0.0f}}, // 6 bottom right back
Vertex{{-0.5f,-0.5f,-0.5f}, {-1.0f, -1.0f, -1.0f},  {0.0f, 0.0f},  {0.0f,0.0f,0.0f}}, // 7 bottom left back
    };
    inline static const std::vector<GLuint> Indices{
        // front
        0, 1, 3,
        2, 3, 0,
        // right
        0, 4, 6,
        0, 2, 6,
        // back
        7, 6, 4,
        4, 5, 7,
        // left
        1, 3, 7,
        1, 5, 7,
        // bottom
        3, 2, 7,
        2, 6, 7,
        // top
        0, 4, 5,
        0, 1, 5
    };

    inline static const std::vector<Vertex> SquareVertices{
		Vertex{{ -0.5f, 0.0f, -0.5f},{0.0f,1.0f,0.0f},  {0.0f, 1.0f}},
    	Vertex{{  0.5f, 0.0f, -0.5f},{0.0f,1.0f,0.0f},  {1.0f, 0.0f}},
        Vertex{{  0.5f, 0.0f,  0.5f},{0.0f,1.0f,0.0f},  {1.0f, 1.0f}},
		Vertex{{ -0.5f, 0.0f,  0.5f},{0.0f,1.0f,0.0f},  {0.0f, 0.0f}}, 
};
    inline static const std::vector<GLuint> SquareIndices{
         0, 1, 2,
    	 0, 3, 2
    };

    
};