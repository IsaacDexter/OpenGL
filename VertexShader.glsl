#version 330 core
// Bind the position to position 0 in the layout
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;

// gl_position is a rare, built in output
out vec2 vTexCoord;

// Uniforms are sort of like constant buffers, they are global scope to the shader
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    // Multiply position by MVP (reverse order as matrix multiplication) to give screen space coords
    gl_Position = uProj * uView * uModel * vec4(inPos, 1.0);
    vTexCoord = inTexCoord;
}