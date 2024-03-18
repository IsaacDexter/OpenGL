#ifndef MESH_H
#define MESH_H

#include "stdafx.h"
#include "Structs.h"


class Mesh
{
public:
	Mesh();
	~Mesh();

	bool CreateVertexBuffer(const GLenum usage);
	bool CreateElementBuffer(const GLenum usage);
	void Bind() const;
	void Draw() const;
private:
	// Vertices of the triangle
	const GLfloat m_vertices[32] = {
		// Position				// Color				// TexCoord
		0.5f,	0.5f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,	1.0f,	// top right
		0.5f,	-0.5f,	0.0f,	0.5f,	0.5f,	0.0f,	1.0f,	0.0f,	// bottom right
		-0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	// bottom left
		-0.5f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,	// top left 
	};

	const GLuint m_indices[6] = {
		0,	1,	3,	// first triangle
		1,	2,	3,	// second triangle
	};
	// A Vertex Buffer Object stores vertex data on the GPU. It is referenced by a UINT ID.
	GLuint m_vbo = 0;
	// An Element Buffer Object stores the indices needed to draw elements
	GLuint m_ebo = 0;
};


#endif // !MESH_H