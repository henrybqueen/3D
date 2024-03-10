#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "../include/utils.h"
#include "../include/shader.h"

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

// Function prototypes
void calculateNormal(vec3 v1, vec3 v2, vec3 v3, vec3 result);
Mesh initMesh(void);
void buildMesh(Mesh* mesh, vec3* points, Face* triangles, size_t numVertices, size_t numFaces);
void loadBuffers(Mesh* mesh);
void drawMesh(GLenum mode, Mesh* mesh, bool drawNormals);

#endif // MESH_H
