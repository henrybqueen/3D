#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stddef.h> // for size_t

// Definition of UniformType enum
typedef enum {
    UNI_FLOAT,
    UNI_VEC3,
    UNI_MAT4,
} UniformType;

// Definition of Uniform struct
typedef struct {
    void* pointer;
    GLint location;
    UniformType type;
} Uniform;

// Definition of ShaderContext struct
typedef struct {
    GLuint shader;
    Uniform* uniforms;
    size_t numUniforms;
} ShaderContext;

// Declaration of setUniform function
void setUniform(Uniform* uniform);

// Declaration of setUniforms function
void setUniforms(ShaderContext* context);

// Declaration of initBuffers function
void initBuffers(GLuint* vao, GLuint* vbo, GLuint* ebo);

#endif // RENDER_H
