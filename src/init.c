#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <string.h>

#include "../include/global.h"
#include "../include/io.h"


// Error callback function
void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}



/* the purpose of this function is simply to initialize glew and glfw, and create a window */
GLFWwindow* init(GlobalContext* context) {


    int width = 800;
    int height = 600;
    float dPos = 0.02f;
    float dOr = 0.001f;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Specify OpenGL version here
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use core profile
    glfwWindowHint(GLFW_SAMPLES, 4); // Request 4x multisampling

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    width = mode->width;
    height = mode->height;

    GLFWwindow* window = glfwCreateWindow(width, height, "App", monitor, NULL);

    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable V-Sync


    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return NULL;
    }

    glViewport(0, 0, width, height); // Set initial viewport size

    glEnable(GL_MULTISAMPLE); // anti aliasing



    /* set callbacks as defined in io.c */
    glfwSetWindowSizeCallback(window, windowSizeCallback); 
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetKeyCallback(window, keyCallback);


    Ray camera = initRay(dPos, dOr);
    InputManager inputManager = {
        .ready = false,
        .x = 0,
        .y = 0,
        .keys = {0} // This initializes all elements to false/0.
    };


    context->camera = camera;
    context->inputManager = inputManager;
    context->needsUpdate = false;
    context->paused = false;
    context->aspect = width / (float)height;

    glfwSetWindowUserPointer(window, context);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return window;
}

void cleanup(GLFWwindow* window) {
    glfwDestroyWindow(window); // Destroy the window created
    glfwTerminate(); // Terminate GLFW
}
