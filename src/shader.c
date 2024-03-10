#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "../include/utils.h"

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


ShaderContext initShaderContext(void) {

    ShaderContext context = {
        .shader = 0,
        .uniforms = NULL,
        .numUniforms = 0
    };

    return context;
}



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


GLuint buildShader(const char* path, GLenum type) {

    char* source = readFile(path);

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar* const*)&source, NULL);

    glCompileShader(shader);

    // Check for shader compile errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
    }

    // free the source memory
    free(source);

    return shader;


}

GLuint buildShaderProgram(const char* vertexPath, const char* geometryPath, const char* fragmentPath) {

    GLuint vertexShader = buildShader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = buildShader(fragmentPath, GL_FRAGMENT_SHADER);
    GLuint geometryShader = 0;

    if (geometryPath) {
        geometryShader = buildShader(geometryPath, GL_GEOMETRY_SHADER);
    }

    // Create shader program
    GLuint shaderProgram = glCreateProgram();

    // Attach shaders
    glAttachShader(shaderProgram, vertexShader);

    if (geometryPath) {
        glAttachShader(shaderProgram, geometryShader);
    }

    glAttachShader(shaderProgram, fragmentShader);

    // Link the shader program
    glLinkProgram(shaderProgram);

    // Check for linking errors
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }

    // Detach and delete shaders after linking
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (geometryPath) {
        glDetachShader(shaderProgram, geometryShader);
        glDeleteShader(geometryShader);
    }

    return shaderProgram;
}



