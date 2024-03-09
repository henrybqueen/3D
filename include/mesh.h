#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stddef.h> // For size_t
#include <stdbool.h> // For bool type

#include "../include/render.h" // Assuming render.h is in the include directory

// Vertex structure representing a vertex with position and normal vectors
typedef struct {
    vec3 position;
    vec3 normal;
} Vertex;

// Face structure representing a triangle in the mesh
typedef struct {
    int vertices[3];
} Face;

// Mesh structure representing a 3D mesh
typedef struct {
    Vertex* vertices;
    Face* faces;
    size_t numVertices;
    size_t numFaces;
    ShaderContext faceShader;
    ShaderContext normalShader;
    GLuint vao, vbo, ebo;
} Mesh;

// Function prototypes
void calculateNormal(vec3 v1, vec3 v2, vec3 v3, vec3 result);
Mesh initMesh(void);
void buildMesh(Mesh* mesh, vec3* points, Face* triangles, size_t numVertices, size_t numFaces);
void loadBuffers(Mesh* mesh);
void drawMesh(GLenum mode, Mesh* mesh, bool drawNormals);

#endif // MESH_H
