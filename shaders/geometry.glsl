#version 330 core

layout(points) in;
layout(line_strip, max_vertices = 2) out;

in vec3 position[];

uniform mat4 view;
uniform mat4 proj;

void main() {

    // Emit the original vertex as the start of the line
    gl_Position = proj * view * vec4(position[0], 1.0);
    EmitVertex();

    // Calculate a new position for the second point of the line
    // This example simply moves the point along the x-axis
    vec3 newPoint = position[0] + vec3(1.0, 0.0, 0.0);

    // Emit the new vertex as the end of the line
    gl_Position = proj * view * vec4(newPoint, 1.0 );
    EmitVertex();

    EndPrimitive(); // End the line primitive
}
