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
