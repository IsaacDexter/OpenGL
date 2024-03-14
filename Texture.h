#ifndef TEXTURE_H
#define TEXTURE_H

#include "stdafx.h"

class Texture
{
private:
	GLuint m_id;
	int m_width, m_height;
public:
	Texture();
	~Texture();

	bool LoadRAW(const char* address, int width, int height);
	bool LoadBMP(const char* address);

	GLuint GetID() const;
	int GetWidth() const;
	int GetHeight() const;
};

#endif // ! TEXTURE_H