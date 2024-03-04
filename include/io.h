#ifndef IO_H
#define IO_H

#include <GLFW/glfw3.h>

void windowSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


#endif // IO_H
