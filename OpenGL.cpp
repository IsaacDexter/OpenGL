// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "glew.h"
#include "freeglut.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")

#define WINDOW_TITLE_PREFIX "OpenGL"

int
CurrentWidth = 800,
CurrentHeight = 600,
WindowHandle = 0;

void Initialize(int, char* []);
void InitWindow(int, char* []);
void InitScene(void);
void ResizeFunction(int, int);
void RenderFunction(void);
std::string LoadShader(const char* address);
void CompileShader(GLuint& id, const GLchar* source, GLenum type);

// A Vertex Buffer Object stores vertex data on the GPU. It is referenced by a UINT ID.
GLuint triangleVbo;

// Vertices of the triangle
float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

// Vertex shader object stored on the GPU, referenced by this ID.
GLuint vertexShader;
// Pixel shader object stored on the GPU, referenced by this ID.
GLuint fragmentShader;

// links both shaders together
GLuint shaderProgram;


int main(int argc, char* argv[])
{
    Initialize(argc, argv);

    InitScene();

    glutMainLoop();

    exit(EXIT_SUCCESS);
}

void Initialize(int argc, char* argv[])
{
    InitWindow(argc, argv);

    fprintf(
        stdout,
        "INFO: OpenGL Version: %s\n",
        glGetString(GL_VERSION)
    );

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void InitWindow(int argc, char* argv[])
{
    glutInit(&argc, argv);


    glutInitContextVersion(4, 0);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );

    glutInitWindowSize(CurrentWidth, CurrentHeight);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

#if defined(_DEBUG)
    if (WindowHandle < 1) {
        fprintf(
            stderr,
            "ERROR: Could not create a new rendering window.\n"
        );
        exit(EXIT_FAILURE);
    }
#endif

    GLenum err = glewInit();

#if defined(_DEBUG)
    if (err != GLEW_OK)
    {
        fprintf(
            stderr,
            "ERROR: Could not initialize GLEW.\n"
        );
        exit(EXIT_FAILURE);
    }
#endif

    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(RenderFunction);
}

void InitScene()
{
    // Generate 1 buffer object corresponding to the stored ID.
    glGenBuffers(1, &triangleVbo);
    // Vertex Buffer Objects use GL_ARRAY_BUFFER type, bind that to the created buffer object to make it a VBO.
    // Also sets the current buffer ID.
    glBindBuffer(GL_ARRAY_BUFFER, triangleVbo);
    // send the triangle vertices to the currently bound vertex buffer. GL_STATIC_DRAW signifies the data is set once and unchanged.
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    std::string vertexShaderString = LoadShader("VertexShader.glsl");
    const GLchar* vertexShaderSource = vertexShaderString.c_str();
    CompileShader(vertexShader, vertexShaderSource, GL_VERTEX_SHADER);

    std::string fragmentShaderString = LoadShader("FragmentShader.glsl");
    const GLchar* fragmentShaderSource = fragmentShaderString.c_str();
    CompileShader(fragmentShader, fragmentShaderSource, GL_FRAGMENT_SHADER);
}

void ResizeFunction(int Width, int Height)
{
    CurrentWidth = Width;
    CurrentHeight = Height;
    glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSwapBuffers();
    glutPostRedisplay();
}

/** 
* Load the glsl as a string. This can be converted to a GLchar* using .c_str().
*/
std::string LoadShader(const char* address)
{
    std::string outShader;

    std::ifstream shaderFile;
    shaderFile.open(address, std::ios::in);
    std::string line;
    // Add each line of the file to the string, appending the newline character

    if (shaderFile.is_open())
    {
        while (std::getline(shaderFile, line))
        {
            outShader.append(line + '\n');
        }
        shaderFile.close();
    }

    return outShader;
}

void CompileShader(GLuint& id, const GLchar* source, GLenum type)
{
    id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    // Check for errors when loading the shader
#if defined(_DEBUG)
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
#endif
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
