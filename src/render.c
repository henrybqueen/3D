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
    GLuint vao, vbo, ebo;
    GLuint shader;
    Uniform* uniforms;
    size_t numUniforms;
} RenderContext;


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

void setUniforms(RenderContext* context) {

    glUseProgram(context->shader); // Activate the shader program

    for (size_t i = 0; i < context->numUniforms; i++) {
        setUniform(&context->uniforms[i]);
    }
}

RenderContext initRenderContext(void) {

    RenderContext context = {
        .vao = 0,
        .vbo = 0,
        .ebo = 0,
        .shader = 0, 
        .uniforms = NULL,
        .numUniforms = 0
    };

    glGenVertexArrays(1, &context.vao);
    glBindVertexArray(context.vao);

    glGenBuffers(1, &context.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, context.vbo);

    glGenBuffers(1, &context.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context.ebo);

    return context;
}

/* this function only worries about deleting the resources that intiRenderContext creates */
void cleanupRenderContext(RenderContext* context) {

    if (context == NULL) {
        return;
    }

    // Delete OpenGL resources
    if (context->vao) {
        glDeleteVertexArrays(1, &context->vao);
        context->vao = 0; // Reset to 0 to indicate it's been deleted
    }

    if (context->vbo) {
        glDeleteBuffers(1, &context->vbo);
        context->vbo = 0; // Reset to 0
    }

    if (context->ebo) {
        glDeleteBuffers(1, &context->ebo);
        context->ebo = 0; // Reset to 0
    }

}



