#ifndef INIT_H 
#define INIT_H

#include <GLFW/glfw3.h>

#include "global.h"

// Function prototype for initializing GLFW and GLEW and creating a window
GLFWwindow* init(GlobalContext* context);
void cleanup(GLFWwindow* window);

#endif // INIT_H
