#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

out vec3 fragPos;
out vec3 fragNormal;


void main() {

    fragPos = pos;
    fragNormal = normal;

    gl_Position = vec4(pos, 1.0);
}
