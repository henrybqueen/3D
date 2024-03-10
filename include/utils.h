#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

float* readBin(const char* path, size_t* num);
char* readFile(const char* filePath);
void printVec3(vec3 v);
void addElement(void** array, size_t* currentSize, void* newElement, size_t elementSize);
void removeElement(void** array, size_t* currentSize, size_t indexToRemove, size_t elementSize);

#endif // UTILS_H
