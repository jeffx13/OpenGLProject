#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/Cubemap.h"
#include "graphics/Model.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "glm/glm.hpp"
#include "Cube.h"
#include "Pyramid.h"
#include "Scene.h"
#include "graphics/Cubemap.h"
#include "graphics/Light.h"
#include "io/Camera.h"
#define shaderf(x) "res/shaders/"##x
#define modelf(x) "res/models/"##x
#define skyboxf(x) "res/skyboxes/"##x


void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
	GLsizei length, const char* message, const void* userParam);

Scene Scene::Instance;
int main()
{
	Scene::init();
	double dt{};
	double lastFrame{};
	double currentFrame{};

	UBO matrices(0, { UBO::MAT4,UBO::MAT4 });

	UBO u_pointlights{ 2 };
	std::vector<Pointlight> pointlights;
	/*for(int i{ 0 };i < 10;i++){
		pointlights.push_back(Pointlight{ {0.0f*i,-0.5f * i,0.00f * i} });
	}
	u_pointlights.setSubData(80, pointlights);*/

	Lamp pointlight1{ Pyramid::Vertices,Pyramid::Indices,Lamp::POINT,{1.0f,1.0f,1.0f} };
	Lamp lamp(Pyramid::Vertices, Pyramid::Indices, Lamp::POINT, glm::vec3(0.0f, 0.5f, 0.0f));

	Cubemap skybox{ skyboxf("akeno")};
	Shader skyboxshader{shaderf("skybox.glsl") };
	
	Model pyramid(Pyramid::Vertices, Pyramid::Indices);
	Model cube(Cube::Vertices, Cube::Indices);

	Model Gintoki(modelf("Gintoki/Gintoki.obj"));
	Model Hata(modelf("Hata/hata.fbx"));
	Model Chika(modelf("Chika_Fujiwara/Chika_Fujiwara.obj"));
	Model merrygo(modelf("merry-go/merryGO.obj"));
	Shader shader(shaderf("res/shaders/object.vert", "res/shaders/object.frag"));
	
	Shader modelshader(shaderf("model.vert"), shaderf("model.frag"));
	Shader test(shaderf("test.vert"), shaderf("test.frag"));
	Shader light_shader(shaderf("model.vert"), shaderf("light.frag"));

	Gintoki.scale(0.01, 0.01, 0.01);
	Gintoki.rotate(120);
	Hata.scale(0.015, 0.015, 0.015);
	Hata.rotate(90, 0, 0);
	Chika.scale(0.5, 0.5, 0.5);
	lamp.scale(0.1, 0.1, 0.1);
	merrygo.scale(0.15, 0.15, 0.15);
	merrygo.rotate(0, -90, 0);
	Gintoki.setPosition(-0.08, 0.7, 0.4);
	Chika.setPosition(0.5, 0, 0.5);
	Hata.setPosition(0, 0, -0.0);

	Camera::setPosition(0, 0.5, 1);
	float angle{};
	float time = 0;
	float radius = 1.5f;
	float period = 600;
	float angular_vel = (2 * glm::pi<float>()) / period;
	while (!glfwWindowShouldClose(Scene::getWindow()))
	{
		currentFrame = glfwGetTime();
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;

		angle += 3;
		Scene::clear();
		Scene::processInputs(dt);
		matrices.setSubData(0, Camera::getView());
		matrices.setSubData(1, Camera::getPerspective());

		skybox.render(skyboxshader);

		lamp.setPosition(0.1*glm::sin(0.05 * time)-0.08, 0.1 * glm::cos(0.05*time) + 0.40, 0.8);
		lamp.render(light_shader,modelshader);
		Gintoki.render(modelshader);
		Chika.render(modelshader);
		Hata.render(modelshader);
		
		merrygo.setPosition(glm::vec3(-glm::sin(angular_vel * time) * radius, 0.0f, radius * glm::cos(angular_vel * time)));
		merrygo.rotate(0, -180/period, 0);
		merrygo.render(modelshader);
		time+=0.5;
		if (glfwGetKey(Scene::getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) { Scene::destroy();break; }
		glfwSwapBuffers(Scene::getWindow());
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	// ignore non-significant error/warning codes
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