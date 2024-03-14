#include "Shader.h"

/// <summary>
/// Creates a program (which encapsulates shaders) and links shaders to it, before detatching them.
/// Deletes all of the shaders queued with Compile.
/// </summary>
/// <returns>If the program linked successfullt</returns>
bool Shader::Link()
{
    // Link shaders together into a program object, an object that encompasses multiple processed shader stages
    for (GLuint shader : m_shaders)
    {
        glAttachShader(m_program, shader);
    }
    glLinkProgram(m_program);

    // Check for errors when linking the shaders
    GLint success;
    char infoLog[512];
    glGetProgramiv(m_program, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        // Log the compilation error
        glGetShaderInfoLog(m_program, 512, NULL, infoLog);
        std::cerr << "ERROR: Could not link program.\n" << infoLog << std::endl;
        return false;
    }

    for (GLuint shader : m_shaders)
    {
        glDetachShader(m_program, shader);
        glDeleteShader(shader);
    }
    m_shaders.clear();

    return true;
}

Shader::Shader()
{
    m_program = glCreateProgram();
}

Shader::~Shader()
{
    glDeleteProgram(m_program);
}

/// <summary>
/// Load and compile a shader of a given type and address.
/// This queues it up for linking with Link()
/// </summary>
/// <param name="address">shader source file to load. must be text equivalent file</param>
/// <param name="type">GL_*_SHADER</param>
/// <returns>if the shader was loaded and compiled successfully</returns>
bool Shader::CompileShader(const char* address, GLenum type)
{
    // Create a shader and store the ID
    GLuint id = glCreateShader(type);



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


    m_shaders.push_back(id);
    return true;
}