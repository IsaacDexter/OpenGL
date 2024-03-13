#include "Renderer.h"

void Renderer::Initialize(int argc, char* argv[])
{
    InitWindow(argc, argv);

    fprintf(
        stdout,
        "INFO: OpenGL Version: %s\n",
        glGetString(GL_VERSION)
    );

    glClearColor(0.0f, 0.0f, 0.5f, 0.0f);

    InitScene();
}

void Renderer::InitWindow(int argc, char* argv[])
{
    glutInit(&argc, argv);


    glutInitContextVersion(4, 0);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );

    glutInitWindowSize(m_width, m_height);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

    m_windowHandle = glutCreateWindow(m_windowTitlePrefix);

    if (m_windowHandle < 1) {
        fprintf(
            stderr,
            "ERROR: Could not create a new rendering window.\n"
        );
        exit(EXIT_FAILURE);
    }

    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        fprintf(
            stderr,
            "ERROR: Could not initialize GLEW.\n"
        );
        exit(EXIT_FAILURE);
    }
}

void Renderer::InitScene()
{
    // Generate and bind a Vertex Array Object (VAO)
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);



    // Generate 1 buffer object corresponding to the stored ID.
    glGenBuffers(1, &m_triangleVbo);
    // Vertex Buffer Objects use GL_ARRAY_BUFFER type, bind that to the created buffer object to make it a VBO.
    // Also sets the current buffer ID.
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVbo);
    // send the triangle vertices to the currently bound vertex buffer. GL_STATIC_DRAW signifies the data is set once and unchanged.
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_triangleVertices), m_triangleVertices, GL_STATIC_DRAW);

    CompileShader(m_vertexShader, "VertexShader.glsl", GL_VERTEX_SHADER);
    CompileShader(m_fragmentShader, "FragmentShader.glsl", GL_FRAGMENT_SHADER);



    // link the shaders in a shader program
    CreateProgram<2>(m_program, { m_vertexShader, m_fragmentShader });

    // Delete the vertex and fragment shaders once they've been bound
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
}

void Renderer::ResizeFunction(int width, int height)
{
    m_width = width;
    m_height = height;
    glViewport(0, 0, m_width, m_height);
}

void Renderer::RenderFunction(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable the program, which contains the vertex and fragment shaders
    glUseProgram(m_program);


    // Draw the scene
    
    // Vertex attributes act as input to the vertex shader
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    // Enable the triangle vertex array. Set to 0 to match the first line of the vertex shader.
    glEnableVertexAttribArray(0);
    glBindVertexArray(m_vao);
    // Bind the triangle's vertex buffer object,
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVbo);

    // Draw the currently bound triangle array
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glUseProgram(0);


    glutSwapBuffers();
    glutPostRedisplay();
}

/// <summary>
/// Load and compile a shader of a given type and address
/// </summary>
/// <param name="id">ID of the shader object</param>
/// <param name="address">shader source file to load. must be text equivalent file</param>
/// <param name="type">GL_*_SHADER</param>
/// <returns>if the shader was loaded and compiled successfully</returns>
bool Renderer::CompileShader(GLuint& id, const char* address, GLenum type)
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
        return false;
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
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        // Log the compilation error
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    return true;
}

/// <summary>
/// Load, bind and store data in an object
/// </summary>
/// <param name="id">ID of the buffer object</param>
/// <param name="vertices">array of vertex data</param>
/// <param name="usage">GL_STATIC_DRAW for static objects</param>
/// <returns>if the buffer was created successfully</returns>
bool Renderer::CreateVertexBuffer(GLuint& id, const GLfloat* vertices, const GLenum usage)
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

/// <summary>
/// Creates a program (which encapsulates shaders) and links shaders to it, before detatching them. Does not delete the shaders.
/// </summary>
/// <typeparam name="size">The number of shaders in the array</typeparam>
/// <param name="id">The program ID</param>
/// <param name="shaders">An array of shaders of size size</param>
/// <returns>If the program linked successfullt</returns>
template<size_t size>
bool Renderer::CreateProgram(GLuint& id, const std::array<GLuint, size> shaders)
{
    // Link shaders together into a program object, an object that encompasses multiple processed shader stages
    id = glCreateProgram();
    for (GLuint shader : shaders)
    {
        glAttachShader(id, shader);
    }
    glLinkProgram(id);

    // Check for errors when linking the shaders
    GLint success;
    char infoLog[512];
    glGetProgramiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        // Log the compilation error
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cerr << "ERROR: Could not link program.\n" << infoLog << std::endl;
        return false;
    }

    for (GLuint shader : shaders)
    {
        glDetachShader(id, shader);
    }

}

