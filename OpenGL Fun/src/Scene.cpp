#include "Scene.h"
#include "graphics/Light.h"
#include "Pyramid.h"
#include "graphics/Model.h"
#include "graphics/Shader.h"
#ifdef ENABLE_DEBUG
#define ENABLE_DEBUG true
#else
#define ENABLE_DEBUG false
#endif


void APIENTRY GLDebugMessageCallback(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam);

std::vector<Lamp> Scene::pointlights;
std::vector<Lamp> Scene::dirlights;
std::vector<Lamp> Scene::spotlights;

void Scene::init()
{
	if (!glfwInit())
		return;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if(ENABLE_DEBUG){ glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE); }
	window = glfwCreateWindow( winwidth, winheight, "Basic Opengl", NULL, NULL);
	
	if (!window) { glfwTerminate();return; }
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "glewInit error!" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

	if (static_cast<bool>(glfwGetWindowAttrib(window, GLFW_OPENGL_DEBUG_CONTEXT)&&ENABLE_DEBUG))
	{
		printf("Enabled debug output\n");
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(GLDebugMessageCallback, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	}
	glViewport(0, 0, winwidth, winheight);

	glEnable(GL_DEPTH_TEST);

	glfwSetKeyCallback(window, Keyboard::keyCallback);
	glfwSetMouseButtonCallback(window, Mouse::buttonCallback);
	glfwSetCursorPosCallback(window, Mouse::posCallback);
	glfwSetScrollCallback(window, Mouse::scrollCallback);
}

void Scene::processInputs(float dt)
{
	if (Keyboard::key(GLFW_KEY_W)) {
		Camera::updatePosition(Directions::FORWARDS, dt);
	}
	if (Keyboard::key(GLFW_KEY_S)) {
		Camera::updatePosition(Directions::BACKWARDS, dt);
	}
	if (Keyboard::key(GLFW_KEY_D)) {
		Camera::updatePosition(Directions::RIGHT, dt);
	}
	if (Keyboard::key(GLFW_KEY_A)) {
		Camera::updatePosition(Directions::LEFT, dt);
	}
	if (Keyboard::key(GLFW_KEY_SPACE)) {
		Camera::updatePosition(Directions::UP, dt);
	}
	if (Keyboard::key(GLFW_KEY_LEFT_SHIFT)) {
		Camera::updatePosition(Directions::DOWN, dt);
	}
	if (Keyboard::key(GLFW_KEY_ESCAPE)) {
		shouldClose = true;
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	Camera::updateZoom();
	Camera::updateFront();
}

void Scene::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Scene::destroy()
{
	for (auto shader : shaders)
	{
		glDeleteProgram(shader);
	}
	for (auto buffer : buffers)
	{
		glDeleteBuffers(1, &buffer);
	}
	for (auto vertexArray : vertexArrays)
	{
		glDeleteVertexArrays(1, &vertexArray);
	}
	for (auto frameBuffer : framebuffers)
	{
		glDeleteFramebuffers(1, &frameBuffer);
	}

}

void Scene::setLightings(Shader shader)
{

	for (int i{ 0 };i < nPointlights;i++) {
		Pointlight pointlight;
		pointlights.push_back({Pyramid::Vertices, Pyramid::Indices, pointlight, shader});

	}
}
void Scene::renderLightings(Shader& shader)
{
	for (int i{ 0 };i < nPointlights;i++)
	{
		pointlights.at(i).render(shader, i);
	}
}

std::vector<Lamp>& Scene::getPointlights()
{
	{ return pointlights; }	
}

std::vector<Lamp>& Scene::getSpotlights()
{
	return spotlights;
}

std::vector<Lamp>& Scene::getDirlights()
{
	return dirlights;
}




void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	GLenum error = glGetError();

	if (error)
	{
		std::cout << "[OpenGL Error] (" << std::hex << error << ") in " << function << " at " << file << " on line " << std::dec << line << std::endl;
		return false;
	}

	return true;
}

void APIENTRY GLDebugMessageCallback(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}


