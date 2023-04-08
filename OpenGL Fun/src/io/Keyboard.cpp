#include "Keyboard.h"

bool Keyboard::keys[GLFW_KEY_LAST] = { 0 };

void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_RELEASE) {
        if (!keys[key]) {
            keys[key] = true;
        }
    }
    else {
        keys[key] = false;
    }
    
}
