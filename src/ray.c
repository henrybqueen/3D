#include <cglm/cglm.h>
#include <GLFW/glfw3.h>
#include <math.h>


/*  
    pos  = 3d coordintaes
    or   = (yaw, pitch) in radians
    dPos = velocity of movement
    dOr = angular velocity
*/
typedef struct {
    vec3 pos;
    vec2 or;
    float dPos;
    float dOr;
} Ray;


Ray initRay(float dPos, float dOr) {

    Ray ray = {
        .pos = {0.0f, 0.0f, 0.0f},
        .or = {0.0f, 0.0f},
        .dPos = dPos,
        .dOr = dOr
    };
    
    return ray;
}


/* populates dest with the view matrix associated with this ray */
void getView(Ray* ray, mat4* dest) {


    vec3 pos;
    glm_vec3_copy(ray->pos, pos);

    float yaw = ray->or[0];
    float pitch = ray->or[1];

  
    versor quatYaw, quatPitch, quatCombined;
    vec3 translate;

    // invert yaw and pitch to achieve correct view
    glm_quatv(quatYaw, -yaw, (vec3){0.0f, 1.0f, 0.0f}); // Global Yaw around world's Y-axis
    glm_quatv(quatPitch, -pitch, (vec3){1.0f, 0.0f, 0.0f}); // Pitch around camera's local X-axis


    // Combine rotations
    glm_quat_mul(quatPitch, quatYaw, quatCombined);
    glm_quat_normalize(quatCombined);

    glm_mat4_identity(*dest);

    // Apply rotation to view matrix
    glm_quat_mat4(quatCombined, *dest);

    // invert pos to achieve correct view
    glm_vec3_scale(pos, -1.0f, pos);

    // Translate 
    glm_translate(*dest, pos);

}

float clamp(float x, float min, float max) {
    return fmin(max, fmax(min, x));
}

void updateOr(Ray* ray, int dx, int dy) {

    ray->or[0] +=  ray->dOr * dx;
    ray->or[1] +=  ray->dOr * dy;

    // restrict pitch to [-pi/2, pi/2]
    ray->or[1] = clamp(ray->or[1], -(M_PI / 2), M_PI / 2);

}


/* update the position of the ray based off of input keys and the current orientation */
void updatePos(Ray* ray, bool* keys) {


    
    int w, a, s, d, sp, sh;

    w = (int)keys[GLFW_KEY_W];
    a = (int)keys[GLFW_KEY_A];
    s = (int)keys[GLFW_KEY_S];
    d = (int)keys[GLFW_KEY_D];
    sp = (int)keys[GLFW_KEY_SPACE];
    sh = (int)keys[GLFW_KEY_LEFT_SHIFT];


    /* if no keys were pressed, then theres nothing to do */
    if (!(w || a || s || d || sp || sh)) {
        return;
    }


    if (keys[GLFW_KEY_W]) {
        printf("W\n");
    }

    float yaw = ray->or[0];
    float pitch = ray->or[1];

    float dx = - (ray->dPos * sin(yaw));
    float dz = - (ray->dPos * cos(yaw));
    float dy = ray->dPos;

    vec3 forward = {dx, 0, dz};
    vec3 left = {dz, 0, -dx};
    vec3 up = {0, dy , 0};

    glm_vec3_scale(forward, w - s, forward);
    glm_vec3_scale(left, a - d, left);
    glm_vec3_scale(up, sp - sh, up);

    glm_vec3_add(forward, ray->pos, ray->pos);
    glm_vec3_add(left, ray->pos, ray->pos);
    glm_vec3_add(up, ray->pos, ray->pos);

}
