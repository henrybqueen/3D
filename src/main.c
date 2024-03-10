#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/init.h"
#include "../include/shader.h"
#include "../include/utils.h"
#include "../include/mesh.h"
#include "../include/ray.h"
#include "../include/global.h"

/*

square = {0, 1, 2, ..., d-1} x {0, 1, 2, ..., d-1}

each vertex (i, j) determines two faces:
    (i, j), (i+1, j), (i+1, j+1)
    (i, j), (i+1, j+1), (i, j+1)


scale is the side length of the square

*/
void buildSquare(Mesh* mesh, float scale, size_t d) {
    

    // allocate memory for the vertices and faces
    vec3* points = (vec3*)malloc(d * d * sizeof(vec3)); 
    Face* faces = (Face*)malloc((d - 1) * (d - 1) * 2 * sizeof(Face)); // 2 triangles per square

    // construct the vertices
    float f;
    float scaled_x, scaled_y;
    for (int x = 0; x < d; x++) {
        for (int y = 0; y < d; y++) {


            scaled_x = scale * (x - d/2.0) / d;
            scaled_y = scale * (y - d/2.0) / d;

            f = sin(scaled_x) * cos(scaled_y);

            glm_vec3_copy((vec3){scaled_x, f , scaled_y}, points[(x * d) + y]);
        }
    } 

    /* each vertex determines two triangles. the vertex at index (i, j) determines two triangles: 1) (i, j), (i+1, j), (i+1, j+1) 2) (i, j), (i+1, j+1), (i, j+1)
        we only want to construct triangles of vertices where i, j < d - 1
    */
   int v, v_right, v_up, v_diag;
   int face1, face2;
    for (int x = 0; x < d - 1; x++) {
        for (int y = 0; y < d - 1; y++) {

        

            // vertices
            v = (x * d) + y;
            v_right = v + d;
            v_up = v + 1;
            v_diag = v_right + 1;

            face1 = 2 * ((x * (d - 1)) + y);
            face2 = 2 * ((x * (d - 1)) + y) + 1;

            // first triangle
            faces[face1].vertices[0] = v;
            faces[face1].vertices[1] = v_right;
            faces[face1].vertices[2] = v_diag;

            // second triangle
            faces[face2].vertices[0] = v;
            faces[face2].vertices[1] = v_diag;
            faces[face2].vertices[2] = v_up;
            
        }
    }

    buildMesh(mesh, points, faces, d * d, (d - 1) * (d - 1) * 2);
    
    free(points);
    free(faces);
}




void main() {

    GlobalContext context;
    GLFWwindow* window = init(&context);

    mat4 proj, view;
    glm_perspective(glm_rad(45.0f), context.aspect, 0.1f, 100.0f, proj);

    Mesh mesh = initMesh();
    buildSquare(&mesh, 10.0f, 100);
    loadBuffers(&mesh);


    mesh.normalShader.shader = buildShaderProgram("../../shaders/normals/vertex.glsl", "../../shaders/normals/geometry.glsl", "../../shaders/normals/fragment.glsl");
    mesh.normalShader.numUniforms = 2;
    mesh.normalShader.uniforms = (Uniform*)malloc(2 * sizeof(Uniform));

    mesh.faceShader.shader = buildShaderProgram("../../shaders/faces/vertex.glsl", NULL, "../../shaders/faces/fragment.glsl");
    mesh.faceShader.numUniforms = 3;
    mesh.faceShader.uniforms = (Uniform*)malloc(3 * sizeof(Uniform));


    Uniform projUniform = {
        .pointer = &proj,
        .location = NULL,
        .type = UNI_MAT4
    };

    Uniform viewUniform = {
        .pointer = &view,
        .location = NULL,
        .type = UNI_MAT4
    };

    Uniform viewPosUniform = {
        .pointer = &(context.camera.pos),
        .location = NULL,
        .type = UNI_VEC3
    };

    // set uniforms for normal shader
    glUseProgram(mesh.normalShader.shader);
    projUniform.location = glGetUniformLocation(mesh.normalShader.shader, "proj");
    viewUniform.location = glGetUniformLocation(mesh.normalShader.shader, "view");

    mesh.normalShader.uniforms[0] = projUniform;
    mesh.normalShader.uniforms[1] = viewUniform;

    // set uniforms for face shader
    glUseProgram(mesh.faceShader.shader);
    projUniform.location = glGetUniformLocation(mesh.faceShader.shader, "proj");
    viewUniform.location = glGetUniformLocation(mesh.faceShader.shader, "view");
    viewPosUniform.location = glGetUniformLocation(mesh.faceShader.shader, "viewPos");

    mesh.faceShader.uniforms[0] = projUniform;
    mesh.faceShader.uniforms[1] = viewUniform;
    mesh.faceShader.uniforms[2] = viewPosUniform;

 

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* ~~~~~~~~~~~~~~~~~ */



        updatePos(&(context.camera), context.inputManager.keys);
        getView(&(context.camera), &view);

        if (context.needsUpdate) {
            glm_perspective(glm_rad(45.0f), context.aspect, 0.1f, 100.0f, proj);
            context.needsUpdate = false;
        }

        drawMesh(GL_TRIANGLES, &mesh, true);


        /* ~~~~~~~~~~~~~~~~~ */

        glfwPollEvents();
        glfwSwapBuffers(window);

    }

    cleanup(window);

}