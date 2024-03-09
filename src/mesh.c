#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "../include/utils.h"
#include "../include/render.h"


// Structure to represent a vertex with a position and a normal
typedef struct {
    vec3 position;
    vec3 normal;
} Vertex;

typedef struct {
    int vertices[3];
} Face;

typedef struct {
    Vertex* vertices;
    Face* faces;
    size_t numVertices;
    size_t numFaces;
    ShaderContext faceShader;
    ShaderContext normalShader;
    GLuint vao, vbo, ebo;
} Mesh;




// Function to calculate the normal of a triangle given three vertices
void calculateNormal(vec3 v1, vec3 v2, vec3 v3, vec3 result) {
    vec3 edge1, edge2;
    glm_vec3_sub(v2, v1, edge1);
    glm_vec3_sub(v3, v1, edge2);
    glm_vec3_cross(edge2, edge1, result);
    glm_vec3_normalize(result);
}


Mesh initMesh(void) {

    Mesh mesh = {
        .vertices = NULL,
        .faces = NULL,
        .numVertices = 0,
        .numFaces = 0
    };

    initBuffers(&(mesh.vao), &(mesh.vbo), &(mesh.ebo));

    glBindVertexArray(mesh.vao);

    // positioin attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    return mesh;
}


/* 

takes positions of vertices and the faces. Computes average normals and populates mesh with vertex and face data.
the arrays points and triangles can be destroyed after calling this methid, as this method deep copies their data.

*/
void buildMesh(Mesh* mesh, vec3* points, Face* triangles, size_t numVertices, size_t numFaces) {

    Vertex* vertices = (Vertex*)malloc(numVertices * sizeof(Vertex));
    Face* faces = (Face*)malloc(numFaces * sizeof(Face));


    /* copy positions into vertices, and init normals to zero */
    for (size_t i = 0; i < numVertices; i++) {
        glm_vec3_zero(vertices[i].normal);
        glm_vec3_copy(points[i], vertices[i].position);
    }

    int v1, v2, v3;
    vec3 normal;


    /* loop over faces and compute average normals for each vertex. Copy each face into faces array */
    for (size_t i = 0; i < numFaces; i++) {

        faces[i] = triangles[i];

        v1 = faces[i].vertices[0];
        v2 = faces[i].vertices[1];
        v3 = faces[i].vertices[2];

        calculateNormal(points[v1], points[v2], points[v3], normal);

        glm_vec3_add(vertices[v1].normal, normal, vertices[v1].normal);
        glm_vec3_add(vertices[v2].normal, normal, vertices[v2].normal);
        glm_vec3_add(vertices[v3].normal, normal, vertices[v3].normal);

    }

    /* normalize the normal for each vertex */
    for (size_t i = 0; i < numVertices; i++) {
        glm_normalize(vertices[i].normal);
    }



    mesh->vertices = vertices;
    mesh->numVertices = numVertices;
 
    mesh->faces = faces;
    mesh->numFaces = numFaces;

}


void loadBuffers(Mesh* mesh) {

    glBindVertexArray(mesh->vao);

    glBufferData(GL_ARRAY_BUFFER, mesh->numVertices * sizeof(Vertex), mesh->vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->numFaces * sizeof(Face), mesh->faces, GL_STATIC_DRAW);

    glBindVertexArray(0);

}


void drawMesh(GLenum mode, Mesh* mesh, bool drawNormals) {


    /* draw faces */
    glBindVertexArray(mesh->vao);
    glUseProgram(mesh->faceShader.shader);

    glEnable(GL_DEPTH_TEST);

    setUniforms(&(mesh->faceShader));
 
    glLineWidth(2.0f);
    //glDrawElements(mode, 3 * mesh->numFaces, GL_UNSIGNED_INT, NULL);

    /* optionally draw normals, which use the same vao */
    if (drawNormals) {
        glUseProgram(mesh->normalShader.shader);
        setUniforms(&(mesh->normalShader));
        glPointSize(5.0f);
        glDrawArrays(GL_POINT, 0, mesh->numVertices);
    }

    glBindVertexArray(0);

}
