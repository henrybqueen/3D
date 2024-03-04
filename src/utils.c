#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>


/* reads the binary files located at path, assumed to be a flat array of floats. Stores the */

float* readBin(const char* path, size_t* num) {

    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("Failed to open file containing star data\n");
        return NULL;
    }

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the buffer
    float *buffer = (float*) malloc(size);
    if (buffer == NULL) {
        printf("Failed to allocate memory for star data\n");
        fclose(file);
        return NULL;
    }

    // Read the entire file into the buffer
    size_t numElements = size / sizeof(float);
    size_t result = fread(buffer, sizeof(float), numElements, file);
    if (result != numElements) {
        printf("Error reading file\n");
        free(buffer);
        fclose(file);
        return NULL;
    }

    fclose(file);

    // Optionally, use sizeDest to pass back the number of elements read
    if (num != NULL) {
        *num = numElements;
    }

    return buffer;
}

char* readFile(const char* filePath) {
    FILE* file = fopen(filePath, "rb"); // Open file in binary mode to read
    char* buffer = NULL;
    
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s for reading.\n", filePath);
        return NULL;
    }
    
    // Seek to the end of the file to determine its size
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file); // Go back to the start of the file
    
    // Allocate memory for the entire file
    buffer = (char*)malloc(length + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    
    // Read the file into the buffer
    size_t readLength = fread(buffer, 1, length, file);
    if (readLength != length) {
        fprintf(stderr, "Error reading file\n");
        free(buffer);
        fclose(file);
        return NULL;
    }
    
    // Null-terminate the string
    buffer[length] = '\0';
    
    // Close the file and return the buffer
    fclose(file);
    return buffer;
}

GLuint buildShaderProgram(const char* vertexPath, const char* fragmentPath) {

    // Load shader source code
    char* vertexShaderSource = readFile(vertexPath);
    char* fragmentShaderSource = readFile(fragmentPath);

    // Create shader objects
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Set shader source
    glShaderSource(vertexShader, 1, (const GLchar* const*)&vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, (const GLchar* const*)&fragmentShaderSource, NULL);

    // Compile shaders
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    // Check for shader compile errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    // Free the shader source memory
    free(vertexShaderSource);
    free(fragmentShaderSource);

    // Create shader program
    GLuint shaderProgram = glCreateProgram();

    // Attach shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Link the shader program
    glLinkProgram(shaderProgram);

    // Check for linking errors
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

    return shaderProgram;
}

void printVec3(vec3 v) {
    printf("(%f, %f, %f)\n", v[0], v[1], v[2]);
}


void addElement(void** array, size_t* currentSize, void* newElement, size_t elementSize) {
    void* newArray = realloc(*array, (*currentSize + 1) * elementSize);
    if (!newArray) {
        printf("Failed to allocate memory\n");
        return;
    }

    memcpy((char*)newArray + (*currentSize * elementSize), newElement, elementSize);
    *array = newArray;
    (*currentSize)++;
}

void removeElement(void** array, size_t* currentSize, size_t indexToRemove, size_t elementSize) {
    if (indexToRemove >= *currentSize) {
        printf("Index out of bounds\n");
        return;
    }

    if (*currentSize > 1) {
        memmove((char*)(*array) + (indexToRemove * elementSize), 
                (char*)(*array) + ((indexToRemove + 1) * elementSize), 
                (*currentSize - indexToRemove - 1) * elementSize);
    }

    void* newArray = realloc(*array, (*currentSize - 1) * elementSize);
    if (newArray || *currentSize == 1) {
        *array = newArray;
        (*currentSize)--;
    } else {
        printf("Failed to reallocate memory\n");
    }
}



