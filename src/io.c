#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "../include/ray.h"
#include "../include/utils.h"
#include "../include/global.h"


void windowSizeCallback(GLFWwindow* window, int width, int height) {

    GlobalContext* context = (GlobalContext*)glfwGetWindowUserPointer(window);

    /* update the aspect ratio, and signal that proj matrix needs update */
    context->aspect = width / (float)height;
    context->needsUpdate = true;

    /* set the size of the viewport  */
    glViewport(0, 0, width, height);

}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {

    GlobalContext* context = (GlobalContext*)glfwGetWindowUserPointer(window);

    // dont do anything if the game is paused
    if (context->paused) {
        return;
    }

    int x, y, dx, dy;

    x = (int) xpos;
    y = (int) ypos;

    if (context->inputManager.ready) {
        dx = context->inputManager.x - x;
        dy = context->inputManager.y -y;
        updateOr(&(context->camera), dx, dy);
    } else {
        context->inputManager.ready = true;
    }
    context->inputManager.x = x;
    context->inputManager.y = y;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {



    GlobalContext* context = (GlobalContext*)glfwGetWindowUserPointer(window);



    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {

        context->paused = !context->paused; // Toggle pause state


        if (context->paused) {

            // Make cursor visible and free it
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            // on pause, release all movement keys
            memset(context->inputManager.keys, 0, sizeof(context->inputManager.keys));


        } else {

            // Hide and capture cursor again
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


            // Indicate that the next mouse callback should ignore the movement
            context->inputManager.ready = false;
        }
    }

    // if the game is not paused, then record movement key presses and releases
    if (!context->paused) {

        if (key >= 0 && key < 1024) {
            if (action == GLFW_PRESS) {
                context->inputManager.keys[key] = true;
            } else if (action == GLFW_RELEASE) {
                context->inputManager.keys[key] = false;
            }
        }
    }

}