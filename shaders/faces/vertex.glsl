#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

out vec3 fragPos;
out vec3 fragNormal;

uniform mat4 view;
uniform mat4 proj;


void main() {

    fragPos = pos;
    fragNormal = normal;

    gl_Position = proj * view * vec4(pos, 1.0);
}
