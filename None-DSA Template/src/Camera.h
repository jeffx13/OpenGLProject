#pragma once
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

static class Camera
{
private:
	double LastTime{ 0 };
	double DeltaTime{ 0 };

	bool firstClick{ true };
	double lastmousex{ 0 };
	double lastmousey{ 0 };
	float Yaw{ -90.0f };
	float Pitch{ 0 };
	float mouse_sensitivity{ 0.6f };
	float scroll_sensitivity{ 2.0f };
	glm::vec3 Position{0.0f, 0.0f, 1.0f};
	glm::vec3 Front{0.0f, 0.0f, -1.0f};
	glm::vec3 Up{0.0f, 1.0f, 0.0f};
	
	const float win_width;
	const float win_height;
	float FOV{ 90.0f };

	void proc_mouse_callback(GLFWwindow* window);
	
public:
	glm::vec3 GetPosition();
	glm::mat4 GetPerspectiveMatrix();
	glm::mat4 GetViewMatrix();
	void proc_scroll_callback(double yoffset);
	void Inputs(GLFWwindow* window);
	Camera(unsigned int width, unsigned int height);
};
