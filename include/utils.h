#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>


float* readBin(const char* path, size_t* num);
char* readFile(const char* filePath);
GLuint buildShaderProgram(const char* vertexPath, const char* fragmentPath);
void addElement(void** array, size_t* currentSize, void* newElement, size_t elementSize);
void removeElement(void** array, size_t* currentSize, size_t indexToRemove, size_t elementSize);

#endif


