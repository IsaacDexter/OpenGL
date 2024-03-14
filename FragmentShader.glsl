#version 330 core
out vec4 FragColor;

// A uniform is a global variable that can be set in the application.
uniform vec4 myColor;

void main()
{
    FragColor = myColor;
} 