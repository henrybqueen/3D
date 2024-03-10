#version 330 core

layout(points) in;
layout(line_strip, max_vertices = 2) out;

uniform mat4 view;
uniform mat4 proj;

in vec3 pos[];
in vec3 normal[];


void main() {

    // Emit the original vertex as the start of the line
    gl_Position = proj * view * vec4(pos[0], 1.0);
    EmitVertex();

    // Calculate a new position for the second point of the line
    // This example simply moves the point along the x-axis
    vec3 newPos = pos[0] + normal[0] * 0.4;

    // Emit the new vertex as the end of the line
    gl_Position = proj * view * vec4(newPos, 1.0);
    EmitVertex();

    EndPrimitive(); // End the line primitive
}