#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;

out vec3 pos;
out vec3 normal;

uniform mat4 view;
uniform mat4 proj;


void main() {

    pos = inPos;
    normal = inNormal;

}
