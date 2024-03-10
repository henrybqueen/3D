#ifndef SHADER_H
#define SHADER_H

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

void setUniform(Uniform* uniform);
void setUniforms(ShaderContext* context);
GLuint buildShader(const char* path, GLenum type);
GLuint buildShaderProgram(const char* vertexPath, const char* geometryPath, const char* fragmentPath);
ShaderContext initShaderContext(void);

#endif // SHADER_H
