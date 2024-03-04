#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

// Enumeration for supported uniform types
typedef enum {
    UNI_FLOAT,
    UNI_VEC3,
    UNI_MAT4,
} UniformType;

// Structure to represent a shader uniform
typedef struct {
    void* pointer;
    GLint location;
    UniformType type;
} Uniform;

// Structure for rendering context
typedef struct {
    GLuint vao, vbo, ebo;
    GLuint shader;
    Uniform* uniforms;
    size_t numUniforms;
} RenderContext;

// Function to set a specific uniform
void setUniform(Uniform* uniform);

// Function to set all uniforms in a context
void setUniforms(RenderContext* context);

// Function to initialize the rendering context
RenderContext initRenderContext(void);

// Function to clean up the rendering context
void cleanupRenderContext(RenderContext* context);

#endif // RENDER_H
