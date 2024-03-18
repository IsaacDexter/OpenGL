#include "Renderer.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    // Enable back face culling
    glEnable(GL_DEPTH_TEST);

    m_rectangle = std::make_shared<Mesh>();
    m_rectangle->CreateVertexBuffer(GL_STATIC_DRAW);
    m_rectangle->CreateElementBuffer(GL_STATIC_DRAW);


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

    // Bind the texture unit to the shader sampler
    m_shader->Use();
    glUniform1i(glGetUniformLocation(m_shader->GetProgram(), "uTexture"), 0);



    // Define vertex attributes
    // Vertex attributes act as input to the vertex shader
    // Position
    glVertexAttribPointer(
        0,                  // Attribute 0, must match that in the vertex shader
        3,                  // Size, 3 = RGB
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        5 * sizeof(float),  // Stride, 0 indicates that vertex attributes are tightly packed in array
        (void*)0            // array buffer offset
    );
    // Enable the position vertex array. Set to 0 to match the first line of the vertex shader.
    glEnableVertexAttribArray(0);
    // Color
    // TexCoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    GLuint uModel = glGetUniformLocation(m_shader->GetProgram(), "uModel");
    m_cube = std::make_shared<Actor>("Cube", m_rectangle, m_battlefieldsForever, uModel);


    // Create the view matrix to represent camera position
    m_view = glm::mat4(1.0f);
    m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, -3.0f));

    // Create the projection matrix, which is aspect ratio dependent.
    m_proj = glm::mat4(1.0f);
    m_proj = glm::perspective(glm::radians(45.0f), m_width / (float)m_height, 0.1f, 100.0f);
}

void Renderer::ResizeFunction(int width, int height)
{
    m_width = width;
    m_height = height;
    glViewport(0, 0, m_width, m_height);

    // Recreate the projection matrix, which is aspect ratio dependent.
    m_proj = glm::mat4(1.0f);
    m_proj = glm::perspective(glm::radians(45.0f), m_width / (float)m_height, 0.1f, 100.0f);
}

void Renderer::RenderFunction(void)
{
    static float degrees = 0.0f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable the program, which contains the vertex and fragment shaders
    m_shader->Use();


    // Set the uniform that corresponds to triangle color.
    //GLuint uniform = glGetUniformLocation(m_program, "uColor");
    //glUniform4f(uniform, m_width/(float)m_height, 0.0f, 0.0f, 1.0f);

    // Draw the scene
    
    // Update MVP
    // Get the uniform MVP matrices in the shader and write the value of the transformation matrix to it.
    //GLuint uModel = glGetUniformLocation(m_shader->GetProgram(), "uModel");
    GLuint uView = glGetUniformLocation(m_shader->GetProgram(), "uView");
    glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(m_view));
    GLuint uProj = glGetUniformLocation(m_shader->GetProgram(), "uProj");
    glUniformMatrix4fv(uProj, 1, GL_FALSE, glm::value_ptr(m_proj));

    m_cube->SetRotation(glm::vec3(degrees));
    degrees+= 0.005f;
    m_cube->Draw();

    // Bind vertex array object to govern state
    glBindVertexArray(m_vao);

    // Actvate the texture unit
    glActiveTexture(GL_TEXTURE0);
    // Bind the Texture
    m_battlefieldsForever->Bind();

    m_rectangle->Draw();


    // Unbind objects for next draw call.
    glBindVertexArray(0);
    glUseProgram(0);


    glutSwapBuffers();
    glutPostRedisplay();
}





