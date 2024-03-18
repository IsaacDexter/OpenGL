#version 330 core
// Bind the position to position 0 in the layout
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexCoord;

// gl_position is a rare, built in output
// color is passed to the fragment shader. The name is a semantic and must match.
out vec3 vColor;
out vec2 vTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);
    //gl_Position = projection * view * model * vec4(position, 1.0f);
    vColor = inColor;
    vTexCoord = inTexCoord;
}