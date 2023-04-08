#pragma once
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

enum class Directions
{
	FORWARDS = 0x0,
	BACKWARDS,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
private:
	Camera() {};
	static inline float yaw{ -90.0f };
	static inline float pitch{ 0 };
	static inline float mouseSen{ 0.6f };
	static inline float camSpeed{ 0.5f };
	static inline float scrollSen{ 2.0f };
	static inline glm::vec3 position{0.0f, 0.0f, 1.0f};
	static inline glm::vec3 front{0.0f, 0.0f, -1.0f};
	static inline glm::vec3 up{0.0f, 1.0f, 0.0f};
	static inline float zoom{ 90.0f };
public:
	static void updateZoom();
	static void updateFront();
	static void updatePosition(Directions direction, float dt);
	static void setPosition(float x, float y, float z);
	static glm::vec3 getPosition();
	static glm::mat4 getPerspective();
	static glm::mat4 getView();
	
	
};
