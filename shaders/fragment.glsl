#version 330 core

in vec3 fragPos;
in vec3 fragNormal;

out vec4 FragColor;

void main() {

    FragColor = vec4(fragPos, 1.0); 
}
