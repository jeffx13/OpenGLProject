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
#include "utility.cpp"

int main()
{
	Scene::init();
	double dt{};
	double lastFrame{};
	double currentFrame{};

	UBO matrices(0, { UBO::MAT4,UBO::MAT4 });
	Scene::setLightings({ shaderf("lights.glsl") });

	Cubemap skybox{ skyboxf("akeno"),{shaderf("skybox.glsl")}};

	Model pyramid(Pyramid::Vertices, Pyramid::Indices);
	Model cube(Cube::Vertices, Cube::Indices);

	Model Gintoki(modelf("Gintoki/Gintoki.obj"));
	Model Hata(modelf("Hata/Hata.obj"));
	Model Chika(modelf("Chika/Chika.obj"));
	Model merrygo(modelf("Merry-Go/Merry-Go.fbx"));

	Model ground(modelf("floor.fbx"));
	ground.scale(0.001, 0.0010, 0.0010);
	Shader modelshader(shaderf("model.vert"), shaderf("model.frag"));
	ground.setPosition(0, 0, 0);
	Gintoki.scale(0.5, 0.5, 0.5);
	//Gintoki.rotate(120.0f);
	Hata.rotate(90, 0, 0);
	Chika.scale(0.5, 0.5, 0.5);
	Scene::getPointlights()[0].scale(0.1, 0.1, 0.1);
	Scene::getPointlights()[1].scale(0.1, 0.1, 0.1);
	merrygo.scale(0.5, 0.5, 0.5);
	merrygo.rotate(0, -90, 0);
	Gintoki.setPosition(-0.08, 0.0, 0.4);
	Chika.setPosition(0.5, 0, 0.5);
	//Hata.setPosition(0, 0, -1.15);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Camera::setPosition(0, 0.5, 1);
	float angle{};
	float time = 0;
	float radius = 3.0f;
	float period = 600;
	float angular_vel = (2 * glm::pi<float>()) / period;
	while (!glfwWindowShouldClose(Scene::getWindow()))
	{
		currentFrame = glfwGetTime();
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;
		matrices.setSubData(0, Camera::getView());
		matrices.setSubData(1, Camera::getPerspective());
		Chika.rotate(0,5);
		Gintoki.rotate(0, 1);

		Scene::clear();
		Scene::processInputs(dt);
		skybox.render();
		Scene::renderLightings(modelshader);
		//Scene::getPointlights()[1].setPosition(Camera::getPosition().x, Camera::getPosition().y, Camera::getPosition().z);
		Scene::getPointlights()[0].setPosition(0.5 * glm::sin(0.05 * time) - 0.08, 0.5 * glm::cos(0.05 * time) + 0.40, 0.8);

		Gintoki.render(modelshader);
		Chika.render(modelshader);
		Hata.render(modelshader);

		for (GLuint i{}; i < 11; i++)
		{
			for (GLuint j{}; j < 10; j++)
			{
				ground.setPosition(-5 + 1.175*i, 0, -5 + 1.175 * j);
				ground.render(modelshader);
			}
		}

		
		Scene::getPointlights()[1].setPosition(glm::vec3(-glm::sin(angular_vel * time) * radius, 0.5f, radius * glm::cos(angular_vel * time)));
		merrygo.setPosition(glm::vec3(-glm::sin(angular_vel * time) * radius, 0.0f, radius * glm::cos(angular_vel * time)));
		merrygo.rotate(0, -180/period, 0);
		merrygo.render(modelshader);
		time += 0.5;
		
		if (glfwGetKey(Scene::getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) { Scene::destroy();break; }
		glfwSwapBuffers(Scene::getWindow());
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
