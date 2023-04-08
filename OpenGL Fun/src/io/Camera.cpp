#include "Camera.h"
#include <iostream>

#include "Mouse.h"
#include "Scene.h"

glm::vec3 Camera::getPosition()
{
	return position;
}

glm::mat4 Camera::getPerspective()
{
	return glm::perspective(glm::radians(zoom), (float)Scene::getWinWidth() / Scene::getWinHeight(), 0.1f, 100.0f);
}

glm::mat4 Camera::getView()
{
    return glm::lookAt(position, position + front, up);;
}

void Camera::updatePosition(Directions direction, float dt)
{
	
	float speed = camSpeed * dt;
	switch(direction)
	{
	case Directions::FORWARDS: position += speed * front; break;
	case Directions::BACKWARDS: position -= speed * front; break;
	case Directions::LEFT: position -= glm::normalize(glm::cross(front, up)) * speed; break;
	case Directions::RIGHT: position += glm::normalize(glm::cross(front, up)) * speed; break;
	case Directions::UP: position += speed * up; break;
	case Directions::DOWN: position -= speed * up; break;
	}
	updateZoom();
	updateFront();
}

void Camera::setPosition(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
}

void Camera::updateZoom()
{
	glm::vec3 _front;
	_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	_front.y = sin(glm::radians(pitch));
	_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(_front);

	zoom -= Mouse::getScrolldy() * scrollSen;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 90.0f)
		zoom = 90.0f;

}

void Camera::updateFront()
{
	if(Mouse::getLeftButton())
	{
		yaw += Mouse::getdx() * mouseSen;
		pitch += Mouse::getdy() * mouseSen;

		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}
		else if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}
	}
	
	
}


