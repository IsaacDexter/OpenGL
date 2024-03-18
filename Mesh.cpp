#include "Mesh.h"
#include "OBJ_Loader.h"

Mesh::Mesh()
{
    
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

/// <summary>
/// Load, bind and store data in an object
/// </summary>
/// <param name="usage">GL_STATIC_DRAW for static objects</param>
/// <returns>if the buffer was created successfully</returns>
bool Mesh::CreateVertexBuffer(const GLenum usage)
{
    // Generate 1 buffer object corresponding to the stored ID.
    glGenBuffers(1, &m_vbo);
    // Vertex Buffer Objects use GL_ARRAY_BUFFER type, bind that to the created buffer object to make it a VBO.
    // Also sets the current buffer ID.
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // send the triangle vertices to the currently bound vertex buffer. GL_STATIC_DRAW signifies the data is set once and unchanged.
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, usage);

    return true;
}

bool Mesh::CreateElementBuffer(const GLenum usage)
{
    // Generate 1 buffer object corresponding to the stored ID.
    glGenBuffers(1, &m_ebo);
    // Vertex Buffer Objects use GL_ARRAY_BUFFER type, bind that to the created buffer object to make it a VBO.
    // Also sets the current buffer ID.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    // send the triangle vertices to the currently bound vertex buffer. GL_STATIC_DRAW signifies the data is set once and unchanged.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, usage);

    return true;
}

void Mesh::Bind() const
{
    // Bind the triangle's vertex buffer object (vertices),
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // and the triangle's element buffer object (indices).
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}

void Mesh::Draw() const
{
    Bind();
    // Initialize Loader
    objl::Loader Loader;
  
    //cout << Loader.LoadedMeshes[0].MeshName << endl;;
    
    Loader.LoadFile("OBJLoader/freddy.obj");

    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_CCW);
    glFrontFace(GL_CCW);
    
    // Draw the currently bound triangle array
    glDrawElements(
        // Load .obj File


        GL_TRIANGLES,       // Drawing mode
        sizeof(m_indices) / sizeof(m_indices[0]),                  // Number of elements to draw
        GL_UNSIGNED_INT,    // Index type
        0                   // Offset
    );
}

