#pragma once
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "io/Camera.h"
#include "io/Mouse.h"
#include "io/Keyboard.h"
#include "graphics/Shader.h"
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
	static Scene getInstance();
	static GLFWwindow* getWindow() { return window; }
	static GLuint getWinWidth() { return winwidth; }
	static GLuint getWinHeight() { return winheight; }
	static void processInputs(float dt);
	static void clear();
	static void destroy();

	static void registerShader(GLuint ID) { shaders.push_back(ID); }
	static void registerBuffer(GLuint ID) { buffers.push_back(ID); }
	static void registerVertexArray(GLuint ID) { vertexArrays.push_back(ID); }
	static void registerFramebuffers(GLuint ID) { framebuffers.push_back(ID); }
private:
	Scene() = default;
	static Scene Instance;
	static inline GLFWwindow* window;
	static inline GLuint winwidth = 1280;
	static inline GLuint winheight = 720;
	 
	static inline glm::mat4 view;
	static inline glm::mat4 projection;
	static inline glm::mat4 textProjection;
	static inline glm::vec3 cameraPos;

	static inline std::vector<GLuint> shaders;
	static inline std::vector<GLuint> buffers;
	static inline std::vector<GLuint> vertexArrays;
	static inline std::vector<GLuint> framebuffers;

	static inline int glfwVersionMajor;
	static inline int glfwVersionMinor;
};

