#ifndef RENDERER_H
#define RENDERER_H

#include "stdafx.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include <array>
#include <glm/mat4x4.hpp>
#include "Actor.h"


class Renderer
{
public:
	void Initialize(int argc, char* argv[]);

	void ResizeFunction(int width, int height);
	void RenderFunction();
	void InitWindow(int argc, char* argv[]);
private:
	
	void InitScene();
private:
	const char* m_windowTitlePrefix = "OpenGL";


	GLint m_width = 800;
	GLint m_height = 600;
	GLint m_windowHandle = 0;

	// shader pipeline Program object, which encapsulates the shader stages in the pipelines
	std::unique_ptr<Shader> m_shader;

	// ID to the Vertex Array Object, which stores vertex attributes that are currently enabled. This allows for switching of vertex states
	GLuint m_vao;

	std::shared_ptr<Mesh> m_rectangle;
	std::shared_ptr<Texture> m_battlefieldsForever;
	std::shared_ptr<Actor> m_cube;

	// The model, view and projection matrices make up the single MVP matrix, which transforms objects into screenspace
	glm::mat4 m_view;
	glm::mat4 m_proj;
};

#endif // !RENDERER_H
