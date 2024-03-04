#ifndef RAY_H // Include guard to prevent double inclusion
#define RAY_H

#include <cglm/cglm.h> // Include CGLM for vector and matrix operations
#include <GLFW/glfw3.h> // Include GLFW for key definitions

// Definition of the Ray structure
typedef struct {
    vec3 pos;  // 3D coordinates for position
    vec2 or;   // Orientation (yaw, pitch) in radians
    float dPos; // Velocity of movement
    float dOr;  // Angular velocity
} Ray;

// Function prototypes
Ray initRay(float dPos, float dOr); // Initialize a Ray object
void getView(Ray* ray, mat4* dest); // Populate dest with the view matrix associated with this ray
float clamp(float x, float min, float max); // Clamp a value between min and max
void updateOr(Ray* ray, int dx, int dy); // Update orientation based on input
void updatePos(Ray* ray, bool* keys); // Update position based on input keys and current orientation

#endif // RAY_H
