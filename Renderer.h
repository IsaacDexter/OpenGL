#ifndef RENDERER_H
#define RENDERER_H

#include "stdafx.h"
#include <array>

class Renderer
{
public:
	void Initialize(int argc, char* argv[]);

	void ResizeFunction(int width, int height);
	void RenderFunction();

private:
	void InitWindow(int argc, char* argv[]);
	void InitScene();

	bool CompileShader(GLuint& id, const char* address, GLenum type);
	bool CreateVertexBuffer(GLuint& id, const GLfloat* vertices, const GLenum usage);
	template<size_t size>
	bool CreateProgram(GLuint& id, const std::array<GLuint, size> shaders);
private:
	const char* m_windowTitlePrefix = "OpenGL";

	// Vertices of the triangle
	const GLfloat m_triangleVertices[9] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	GLint m_width = 800;
	GLint m_height = 600;
	GLint m_windowHandle = 0;

	// A Vertex Buffer Object stores vertex data on the GPU. It is referenced by a UINT ID.
	GLuint m_triangleVbo;

	// Vertex shader object stored on the GPU, referenced by this ID.
	GLuint m_vertexShader;
	// Fragment (pixel) shader object stored on the GPU, referenced by this ID.
	GLuint m_fragmentShader;

	// shader pipeline Program object, which encapsulates the shader stages in the pipelines
	GLuint m_program;

	// ID to the Vertex Array Object, which stores vertex attributes that are currently enabled. This allows for switching of vertex states
	GLuint m_vao;
};

#endif // !RENDERER_H
