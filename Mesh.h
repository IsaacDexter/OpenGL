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
	const GLfloat m_vertices[(3 + 2) * 8] = {
        // Position				//TexCoord
		0.5f,	0.5f,	-0.5f,	0.0f,	1.0f,	// Front Top Right
		0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	// Front Bottom Right
		-0.5f,	-0.5f,	-0.5f,	1.0f,	0.0f,	// Front Bottom Left
		-0.5f,	0.5f,	-0.5f,	1.0f,	1.0f,	// Front Top Left
		
		0.5f,	0.5f,	0.5f,	1.0f,	1.0f,	// Back Top Right
		0.5f,	-0.5f,	0.5f,	1.0f,	0.0f,	// Back Bottom Right
		-0.5f,	-0.5f,	0.5f,	0.0f,	0.0f,	// Back Bottom Left
		-0.5f,	0.5f,	0.5f,	0.0f,	1.0f,	// Back Top Left
    };

	const GLuint m_indices[6 * 6] = {
		2,	1,	0,
		2,	0,	3,	// Front

		1,	5,	4,
		1,	4,	0,	// Right

		3,	0,	4,
		3,	4,	7,	// Top

		5,	6,	7,
		5,	7,	4,	// Back

		6,	2,	3,
		6,	3,	7,	// Left

		6,	5,	1,
		6,	1,	2,
	};
	// A Vertex Buffer Object stores vertex data on the GPU. It is referenced by a UINT ID.
	GLuint m_vbo = 0;
	// An Element Buffer Object stores the indices needed to draw elements
	GLuint m_ebo = 0;
};


#endif // !MESH_H