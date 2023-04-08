#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
class Mouse
{
public:
    Mouse(const Mouse&) = delete;

    static void posCallback(GLFWwindow* window, double xpos, double ypos);
    static void buttonCallback(GLFWwindow* window, int button, int action, int mods);
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    static bool getLeftButton() { return leftDown; }
    static double getx() { return x; }
    static double gety()  { return y; }
    static double getlastX()  { return lastX; }
    static double getlastY()  { return lastY; }
    static double getdx() { double _dx = dx; dx = 0; return _dx; }
    static double getdy()  { double _dy = dy; dy = 0; return _dy; }
    static double getScrolldy()  { double _scrollDy = scrolldy; scrolldy = 0; return _scrollDy; }
private:
    Mouse(){}
    static Mouse Instance;
    static inline double x;
    static inline double y;
    static inline double lastX;
    static inline double lastY;
    static inline double dx = 0;
    static inline double dy = 0;
  
    static inline bool leftDown;
    static inline bool rightDown;

    static inline double scrolldy = 0;
    static inline bool firstClick = true;
};

