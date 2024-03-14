#ifndef SHADER_H
#define SHADER_H

#include "stdafx.h"
#include <vector>

class Shader
{
public:
	Shader();
	~Shader();

	bool CompileShader(const char* address, GLenum type);
	bool Link();

	GLuint GetProgram() const { return m_program; }
	void Use() const { glUseProgram(m_program); }
private:
	std::vector<GLuint> m_shaders;
	GLuint m_program;
};

#endif // !SHADER_H
