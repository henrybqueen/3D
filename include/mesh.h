#ifndef MESH_H
#define MESH_H

#include <cglm/cglm.h>

#include "render.h"


// Structure to represent a vertex with a position and a normal
typedef struct {
    vec3 position;
    vec3 normal;
} Vertex;

// Structure to represent a face using indices to vertices
typedef struct {
    int vertices[3];
} Face;

// Structure to represent a mesh with vertices, faces, and rendering context
typedef struct {
    Vertex* vertices;
    Face* faces;
    size_t numVertices;
    size_t numFaces;
    RenderContext context;
} Mesh;

// Function prototypes
void calculateNormal(vec3 v1, vec3 v2, vec3 v3, vec3 result);
Mesh initMesh(void);
void buildMesh(Mesh* mesh, vec3* points, Face* triangles, size_t numVertices, size_t numFaces);
void loadBuffers(Mesh* mesh);
void drawMesh(GLenum mode, Mesh* mesh);
void cleanupMesh(Mesh* mesh);

#endif // MESH_H
