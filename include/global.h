#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdbool.h>

#include "ray.h"


typedef struct {
    bool ready;
    int x, y;
    bool keys[1024];
} InputManager;


typedef struct {
    Ray camera;
    InputManager inputManager;
    float aspect;
    bool paused;
    bool needsUpdate;
} GlobalContext;

#endif