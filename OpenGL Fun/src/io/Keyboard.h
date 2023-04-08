#pragma once
#include <GLFW/glfw3.h>

class Keyboard
{
public:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool key(int key) { return keys[key]; }
private:
	Keyboard() = default;
	static bool keys[];
};

