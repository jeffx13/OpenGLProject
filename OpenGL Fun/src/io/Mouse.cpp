#include "Mouse.h"

#include <iostream>



void Mouse::posCallback(GLFWwindow* window, double xpos, double ypos)
{
	x = xpos;
	y = ypos;
	
	if (firstClick) {
		lastX = x;
		lastY = y;
		firstClick = false;
	}

	dx = x - lastX;
	dy = lastY - y;
	lastX = x;
	lastY = y;

	
}

void Mouse::buttonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		leftDown = true;
		if (firstClick)
		{
			lastX = x;
			lastY = y;
			firstClick = false;
			std::cout << "click";
		}

	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		firstClick = true;
		leftDown = false;
		std::cout << "release";
		
		
	}
}

void Mouse::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	scrolldy = yOffset;
}
