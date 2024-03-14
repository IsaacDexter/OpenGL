#version 330 core
// Input color from vertex shader
in vec3 vColor;


// The color of this fragment
out vec4 fColor;

// A uniform is a global variable that can be set in the application.
// uniform vec4 uColor;

void main()
{
    fColor = vec4(vColor, 1.0);
} 