#version 330 core

layout(points) in;
layout(line_strip, max_vertices = 2) out;

uniform mat4 view;
uniform mat4 proj;


void main() {

    // Original vertex position, assuming it's passed from the vertex shader
    vec4 originalPos = gl_in[0].gl_Position;

    // Emit the original vertex as the start of the line
    gl_Position = proj * view * originalPos;
    EmitVertex();

    // Calculate a new position for the second point of the line
    // This example simply moves the point along the x-axis
    vec4 newPoint = originalPos + vec4(0.0, 1.0, 0.0, 0.0);

    // Emit the new vertex as the end of the line
    gl_Position = proj * view * newPoint;
    EmitVertex();

    EndPrimitive(); // End the line primitive
}
