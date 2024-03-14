#include "Renderer.h"
#include "Shader.h"

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


    CreateVertexBuffer(m_vbo, m_vertices, sizeof(m_vertices), GL_STATIC_DRAW);
    CreateElementBuffer(m_ebo, m_indices, sizeof(m_indices), GL_STATIC_DRAW);


    m_shader = std::make_unique<Shader>();
    m_shader->CompileShader("VertexShader.glsl", GL_VERTEX_SHADER);
    m_shader->CompileShader("FragmentShader.glsl", GL_FRAGMENT_SHADER);

    // link the shaders in a shader program
    m_shader->Link();

    // Set to wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Set to fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



    // Load the textures
    m_battlefieldsForever = std::make_shared<Texture>();
    m_battlefieldsForever->LoadBMP("assets/textures/BattlefieldsForever.bmp");

    // Bind the texture unity to the shader sampler
    m_shader->Use();
    glUniform1i(glGetUniformLocation(m_shader->GetProgram(), "uTexture"), 0);
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
    m_shader->Use();


    // Set the uniform that corresponds to triangle color.
    //GLuint uniform = glGetUniformLocation(m_program, "uColor");
    //glUniform4f(uniform, m_width/(float)m_height, 0.0f, 0.0f, 1.0f);

    // Draw the scene
    

    // Vertex attributes act as input to the vertex shader
    // Position
    glVertexAttribPointer(
        0,                  // Attribute 0, must match that in the vertex shader
        3,                  // Size, 3 = RGB
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        8 * sizeof(float),  // Stride, 0 indicates that vertex attributes are tightly packed in array
        (void*)0            // array buffer offset
    );
    // Enable the position vertex array. Set to 0 to match the first line of the vertex shader.
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // TexCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);



    // Bind vertex array object to govern state
    glBindVertexArray(m_vao);
    // Bind the triangle's vertex buffer object (vertices),
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // and the triangle's element buffer object (indices).
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

    // Actuvate thge texture unit
    glActiveTexture(GL_TEXTURE0);
    // Bind the Texture
    glBindTexture(GL_TEXTURE_2D, m_battlefieldsForever->GetID());



    // Draw the currently bound triangle array
    glDrawElements(
        GL_TRIANGLES,       // Drawing mode
        6,                  // Number of elements to draw
        GL_UNSIGNED_INT,    // Index type
        0                   // Offset
    );


    // Unbind objects for next draw call.
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glUseProgram(0);


    glutSwapBuffers();
    glutPostRedisplay();
}

/// <summary>
/// Load, bind and store data in an object
/// </summary>
/// <param name="id">ID of the buffer object</param>
/// <param name="vertices">array of vertex data</param>
/// <param name="size">sizeof(vertices)</param>
/// <param name="usage">GL_STATIC_DRAW for static objects</param>
/// <returns>if the buffer was created successfully</returns>
bool Renderer::CreateVertexBuffer(GLuint& id, const GLfloat* vertices, const size_t size, const GLenum usage)
{
    // Generate 1 buffer object corresponding to the stored ID.
    glGenBuffers(1, &id);
    // Vertex Buffer Objects use GL_ARRAY_BUFFER type, bind that to the created buffer object to make it a VBO.
    // Also sets the current buffer ID.
    glBindBuffer(GL_ARRAY_BUFFER, id);
    // send the triangle vertices to the currently bound vertex buffer. GL_STATIC_DRAW signifies the data is set once and unchanged.
    glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);

    return true;
}

bool Renderer::CreateElementBuffer(GLuint& id, const GLuint* indices, const size_t size, const GLenum usage)
{
    // Generate 1 buffer object corresponding to the stored ID.
    glGenBuffers(1, &id);
    // Vertex Buffer Objects use GL_ARRAY_BUFFER type, bind that to the created buffer object to make it a VBO.
    // Also sets the current buffer ID.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    // send the triangle vertices to the currently bound vertex buffer. GL_STATIC_DRAW signifies the data is set once and unchanged.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);

    return true;
}



