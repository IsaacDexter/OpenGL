#version 330 core
// Input color from vertex shader
in vec3 vColor;
in vec2 vTexCoord;

// The color of this fragment
out vec4 fColor;

// A uniform is a global variable that can be set in the application.
uniform sampler2D uTexture;

void main()
{
    // fColor = vec4(vColor, 1.0);
    // Sample the color fo the texture using the texture and coordinate
    fColor = texture(uTexture, vTexCoord) * vec4(vColor, 1.0f);
} 