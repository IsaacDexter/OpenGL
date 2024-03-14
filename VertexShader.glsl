#version 330 core
// Bind the position to position 0 in the layout
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inColor;

// gl_position is a rare, built in output
// color is passed to the fragment shader. The name is a semantic and must match.
out vec3 vColor;

void main()
{
    gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);
    vColor = inColor;
}