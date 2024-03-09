#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/init.h"
#include "../include/render.h"
#include "../include/utils.h"
#include "../include/mesh.h"
#include "../include/ray.h"
#include "../include/global.h"



void main() {

    GlobalContext context;
    GLFWwindow* window = init(&context);

    mat4 proj, view;
    glm_perspective(glm_rad(45.0f), context.aspect, 0.1f, 100.0f, proj);


    GLuint vao, vbo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float points[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };


    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    GLuint shader = buildShaderProgram("shaders/vertex.glsl", "shaders/geometry.glsl", "shaders/fragment.glsl");
    glUseProgram(shader);

    GLint projLoc = glGetUniformLocation(shader, "proj");
    GLint viewLoc = glGetUniformLocation(shader, "view");


    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &(proj[0][0]));



    while (!glfwWindowShouldClose(window)) {


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* ~~~~~~~~~~~~~~~~~ */



        updatePos(&(context.camera), context.inputManager.keys);

        getView(&(context.camera), &view);

        if (context.needsUpdate) {
            glm_perspective(glm_rad(45.0f), context.aspect, 0.1f, 100.0f, proj);
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, &(proj[0][0]));
            context.needsUpdate = false;
        }

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(view[0][0]));

        glPointSize(10.0f);
        glDrawArrays(GL_POINTS, 0, 3);

        /* ~~~~~~~~~~~~~~~~~ */

        glfwPollEvents();
        glfwSwapBuffers(window);

    }

    cleanup(window);

}