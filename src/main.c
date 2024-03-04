#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/init.h"
#include "../include/render.h"
#include "../include/utils.h"
#include "../include/mesh.h"
#include "../include/ray.h"
#include "../include/global.h"

void main() {

    int width = 800;
    int height = 600;

    float dPos = 0.1f;
    float dOr = 0.1f;

    GlobalContext context;
    GLFWwindow* window = init(&context);

    mat4 proj, view;
    glm_perspective(glm_rad(45.0f), context.aspect, 0.1f, 100.0f, proj);


    Mesh mesh = initMesh();

    vec3 points[] = {
        {-1.0f, 0.0f, 0.0f}, 
        {-1.0f, 0.0f, -1.0f},
        {1.0f, 0.0f, -1.0f},
        {0.0f, 1.0f, -1.0f}
    };

    Face triangles[] = {
        {.vertices={0, 1, 2}},
        {.vertices={0, 2, 3}},
        {.vertices={0, 1, 3}},
        {.vertices={1, 2, 3}},
    };

    buildMesh(&mesh, points, triangles, 4, 4);

    loadBuffers(&mesh);

    mesh.context.numUniforms = 2;
    mesh.context.uniforms = (Uniform*)malloc(2 * sizeof(Uniform));

    mesh.context.shader = buildShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
    glUseProgram(mesh.context.shader);


    Uniform projUniform = {
        .pointer = &proj,
        .location = glGetUniformLocation(mesh.context.shader, "proj"),
        .type = UNI_MAT4
    };

    Uniform viewUniform = {
        .pointer = &view,
        .location = glGetUniformLocation(mesh.context.shader, "view"),
        .type = UNI_MAT4
    };

 
    mesh.context.uniforms[0] = projUniform;

    mesh.context.uniforms[1] = viewUniform;


    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* ~~~~~~~~~~~~~~~~~ */



        updatePos(&(context.camera), context.inputManager.keys);
        //printf("%f %f %f\n", context.camera.pos[0], context.camera.pos[1], context.camera.pos[2]);
        getView(&(context.camera), &view);

        if (context.needsUpdate) {
            glm_perspective(glm_rad(45.0f), context.aspect, 0.1f, 100.0f, proj);
            context.needsUpdate = false;
        }

        drawMesh(GL_TRIANGLES, &mesh);


        /* ~~~~~~~~~~~~~~~~~ */

        glfwPollEvents();
        glfwSwapBuffers(window);

    }

    cleanup(window);

}