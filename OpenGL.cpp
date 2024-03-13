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
bool CompileShader(GLuint& id, const char* address, GLenum type);
bool LoadVertexBuffer(GLuint& id, const GLfloat* vertices, const GLenum usage);

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
// Fragment (pixel) shader object stored on the GPU, referenced by this ID.
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
    LoadVertexBuffer(triangleVbo, triangleVertices, GL_STATIC_DRAW);

    CompileShader(vertexShader, "VertexShader.glsl", GL_VERTEX_SHADER);
    CompileShader(fragmentShader, "FragmentShader.glsl", GL_FRAGMENT_SHADER);
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
* Load and compile a shader of a given type and address
* @param id - ID of the shader object
* @param address - shader source file to load. must be text equivalent file
* @param type - GL_*_SHADER
* @returns success/failure
*/
bool CompileShader(GLuint& id, const char* address, GLenum type)
{
    // Create a shader and store the ID
    id = glCreateShader(type);



    // Load the shader file 
    std::string contents = "";
    std::ifstream file;
    file.open(address, std::ios::in);

    // Ensure the file could in fact be opened 
    if (!file.is_open())
    {
        std::cerr << "ERROR: Failed to open " << address << std::endl;
    }
    // Assign the contents of the file to the string by iterating through the file
    contents.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    file.close();
    const GLchar* source = contents.c_str();



    // Compile the shader from the char array
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);



    // Check for errors when compiling the shader
    GLint success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        // Log the compilation error
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    return true;
}

/** 
* Load, bind and store data in an object
* @param id - ID of the buffer object
* @param target - array of vertex data
* @param usage - GL_STATIC_DRAW for static objects
* @returns success/failure
*/
bool LoadVertexBuffer(GLuint& id, const GLfloat* vertices, const GLenum usage)
{
    // Generate 1 buffer object corresponding to the stored ID.
    glGenBuffers(1, &id);
    // Vertex Buffer Objects use GL_ARRAY_BUFFER type, bind that to the created buffer object to make it a VBO.
    // Also sets the current buffer ID.
    glBindBuffer(GL_ARRAY_BUFFER, id);
    // send the triangle vertices to the currently bound vertex buffer. GL_STATIC_DRAW signifies the data is set once and unchanged.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, usage);

    return true;
}
