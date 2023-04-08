#include "Scene.h"


void Scene::init()
{
	if (!glfwInit())
		return;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow( winwidth, winheight, "Basic Opengl", NULL, NULL);

	if (!window) { glfwTerminate();return; }
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "glewInit error!" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

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