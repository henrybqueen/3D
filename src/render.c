#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>


/* these are the types which are supported by this engine */
typedef enum {
    UNI_FLOAT,
    UNI_VEC3,
    UNI_MAT4,
} UniformType;

typedef struct {
    void* pointer;
    GLint location;
    UniformType type;
} Uniform;

typedef struct {
    GLuint shader;
    Uniform* uniforms;
    size_t numUniforms;
} ShaderContext;


void setUniform(Uniform* uniform) {
    switch(uniform->type) {
        case UNI_FLOAT:
            glUniform1f(uniform->location, *(float*)(uniform->pointer)); 
            break;
        case UNI_VEC3:
            glUniform3fv(uniform->location, 1, (float*)(uniform->pointer));
            break;
        case UNI_MAT4:
            glUniformMatrix4fv(uniform->location, 1, GL_FALSE, (float*)uniform->pointer);
            break;
    }
}

void setUniforms(ShaderContext* context) {

    glUseProgram(context->shader); // Activate the shader program

    for (size_t i = 0; i < context->numUniforms; i++) {
        setUniform(&context->uniforms[i]);
    }
}

void initBuffers(GLuint* vao, GLuint* vbo, GLuint* ebo) {

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);

    if (ebo) {
        glGenBuffers(1, ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    }

    glBindVertexArray(0);

}




