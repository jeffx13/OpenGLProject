#pragma once
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "io/Camera.h"
#include "io/Mouse.h"
#include "io/Keyboard.h"
#include <iostream>

#include <vector>

#define ASSERT(x) if (!(x)) __debugbreak(); 
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
class Scene
{
public:
	Scene(const Scene&) = delete;
	static void init();
	static GLFWwindow* getWindow() { return window; }
	static GLuint getWinWidth() { return winwidth; }
	static GLuint getWinHeight() { return winheight; }
	static GLboolean getShouldClose() { return shouldClose; }

	static void processInputs(float dt);
	static void clear();
	static void destroy();
	
	static void registerShader(GLuint ID) { shaders.push_back(ID); }
	static void registerBuffer(GLuint ID) { buffers.push_back(ID); }
	static void registerVertexArray(GLuint ID) { vertexArrays.push_back(ID); }
	static void registerFramebuffers(GLuint ID) { framebuffers.push_back(ID); }
	static void setLightings(class Shader shader);
	static void renderLightings(Shader& shader);
	static GLuint getnDirlights() { return nDirlights; }
	static GLuint getnPointlights() { return nPointlights; }
	static GLuint getnSpotlights() { return nSpotlights; }
	static std::vector<class Lamp>& getPointlights();
	static std::vector<Lamp>& getSpotlights();
	static std::vector<Lamp>& getDirlights();
private:
	Scene() = default;
	static inline GLuint nDirlights{ 1 };
	static inline GLuint nPointlights{ 2 };
	static inline GLuint nSpotlights{ 10 };
	static std::vector<Lamp> pointlights;
	static std::vector<Lamp> spotlights;
	static std::vector<Lamp> dirlights;

	static inline GLFWwindow* window;
	static inline GLuint winwidth = 1280;
	static inline GLuint winheight = 720;
	static inline GLboolean shouldClose = false;
	static inline glm::mat4 textProjection;


	static inline std::vector<GLuint> shaders;
	static inline std::vector<GLuint> buffers;
	static inline std::vector<GLuint> vertexArrays;
	static inline std::vector<GLuint> framebuffers;

	static inline int glfwVersionMajor;
	static inline int glfwVersionMinor;

};

