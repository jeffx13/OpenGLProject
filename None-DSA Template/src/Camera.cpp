#include "Camera.h"
#include <iostream>
Camera::Camera(unsigned int width, unsigned int height)
	:win_width(width), win_height(height)
{
	
}

glm::vec3 Camera::GetPosition()
{
	return Position;
}

glm::mat4 Camera::GetPerspectiveMatrix()
{
	return glm::perspective(glm::radians(FOV), win_width / win_height, 0.1f, 100.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);;
}

void Camera::Inputs(GLFWwindow* window)
{
	auto now = glfwGetTime();
	DeltaTime = now - LastTime;
	LastTime = now;
	float cameraSpeed = 0.5f * DeltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += cameraSpeed * Front;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position -= cameraSpeed * Front;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position -= glm::normalize(glm::cross(Front, Up)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += glm::normalize(glm::cross(Front, Up)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += cameraSpeed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		Position -= cameraSpeed * Up;
	}
	
	proc_mouse_callback(window);
}

void Camera::proc_mouse_callback(GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CROSSHAIR_CURSOR);

		if (firstClick)
		{
			glfwGetCursorPos(window, &lastmousex, &lastmousey);
			firstClick = false;
		}

		double xpos;
		double ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		float xoffset = xpos - lastmousex;
		float yoffset = lastmousey - ypos;
		lastmousex = xpos;
		lastmousey = ypos;

		xoffset *= mouse_sensitivity;
		yoffset *= mouse_sensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}
		else if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}

		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);

	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		firstClick = true;
	}

}

void Camera::proc_scroll_callback(double yoffset){
	FOV -= (float)yoffset * scroll_sensitivity;
	if (FOV < 1.0f)
		FOV = 1.0f;
	if (FOV > 90.0f)
		FOV = 90.0f;
}

