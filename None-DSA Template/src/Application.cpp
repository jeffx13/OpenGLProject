#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Cubemap.h"
#include "Model.h"
#include "Mesh.h"
#include "graphics/Renderer.h"
#include "glm/glm.hpp"

#include "Cube.h"
#include "Pyramid.h"
#include "Light.h"
#include "Camera.h"

glm::mat4 proj;
glm::mat4 view;
unsigned int win_width = 1280;
unsigned int  win_height = 720;
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void SetMVP(Shader& shader, glm::mat4& model);
Camera camera(win_width, win_height);
int main()
{
	
	GLFWwindow* window;
	Renderer renderer;

	glm::mat4 model;
	glm::mat4 mvp;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(win_width, win_height, "Basic Opengl", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "glewInit error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
	GLCall(glViewport(0, 0, win_width, win_height));

	GLCall(glEnable(GL_DEPTH_TEST));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	glfwSetScrollCallback(window, scroll_callback);

	{
		Cubemap skybox{ "res/skyboxes/default" };
		Shader skyboxshader{ "res/shaders/skybox.vert","res/shaders/skybox.frag" };
		
		Mesh pyramid(Pyramid::Vertices, Pyramid::Indices);
		Mesh cube(Cube::Vertices, Cube::Indices);
		
		Light light(Cube::Vertices, Cube::Indices, {1.0, 1.0, 1.0}, {1.5, 1.5, 1.5}, {1.5, 1.5, 1.5},{1.5, 1.5, 1.5});

		

		Model Gintoki("res/models/Gintoki/Gintoki.fbx");
		Model Chika("res/models/Chika_Fujiwara/Chika_Fujiwara.obj");

		Shader shader("res/shaders/object.vert", "res/shaders/object.frag");
		shader.Bind();
		shader.Set1i("u_Texture", 0);
		Shader modelshader("res/shaders/model.vert", "res/shaders/model.frag");
		Shader light_shader("res/shaders/object.vert", "res/shaders/light.frag");
		//Shader basic_shader("res/shaders/Basic.shader");
		auto angle = 0;
		cube.UseDefaultTexture();
		cube.SetPosition(0, 0, 0);
		while (!glfwWindowShouldClose(window))
		{
			view = camera.GetViewMatrix();
			proj = camera.GetPerspectiveMatrix();
			renderer.Clear();
			skybox.render(skyboxshader, view, proj);
			camera.Inputs(window);
			
			/*light.colour.x = (float)glm::sin(glfwGetTime());
			light.colour.y = (float)glm::cos(glfwGetTime());
			light.colour.z = (float)glm::tan(glfwGetTime());*/

			shader.Bind();
			shader.Set1i("u_Texture", 0.0);
			SetMVP(shader, pyramid.ModelMatrix);

			modelshader.Bind();
			modelshader.Set3f("light.colour", light.colour);
			modelshader.Set3f("light.pos", camera.GetPosition());
			modelshader.Set3f("light.ambient", light.ambient);
			modelshader.Set3f("light.diffuse", light.diffuse);
			modelshader.Set3f("light.specular", light.specular);
			modelshader.Set3f("viewPos", camera.GetPosition());
			modelshader.Set3f("lightPos", camera.GetPosition());
			
			angle += 3;
			Gintoki.SetPosition(glm::vec3(glm::cos(glfwGetTime()*2)*0.5, 0.0f, 0.5*glm::sin(glfwGetTime()*2)));
			Gintoki.SetScale(0.01, 0.01, 0.01);
			Gintoki.Rotate(angle,-angle, angle);
			SetMVP(modelshader, Gintoki.meshes[0].ModelMatrix);
			
			Gintoki.render(modelshader,2);

			Chika.SetPosition(0, 0, 0);
			Chika.SetScale(1, 1, 1);
			Chika.Rotate(0,angle);
			SetMVP(modelshader, Chika.ModelMatrix);
			Chika.render(modelshader);

			light.SetPosition(0, 1.0f, 0);
			light.SetScale(0.1, 0.1, 0.1);
			light_shader.Bind();
			light_shader.Set3f("light_colour", light.colour);
			SetMVP(light_shader, light.ModelMatrix);
			light.render(light_shader);

			light.SetPosition(0, 0.0f, 0);
			SetMVP(light_shader, light.ModelMatrix);

			//cube.render(shader);
			

			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { break; }
			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());
		}
	}

	glfwTerminate();
	return 0;
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.proc_scroll_callback(yOffset);
	
}

//void construct_object(VertexArray& VA, Shape& shape, IndexBuffer& IBO)
//{
//	VA.Bind();
//	VertexBuffer VBO(shape.Vertices);
//	VA.AddBuffer(VBO, shape.Layout);
//	IBO.Bind();
//	VA.Unbind();
//	VBO.Unbind();
//	IBO.Unbind();
//}

void SetMVP(Shader& shader, glm::mat4& model)
{
	view = camera.GetViewMatrix();
	proj = camera.GetPerspectiveMatrix();
	shader.Bind();
	shader.SetMat4f("model", model);
	shader.SetMat4f("view", view);
	shader.SetMat4f("projection", proj);
}
