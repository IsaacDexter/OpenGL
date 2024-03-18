#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>


using namespace glm;
using namespace std;

struct Vertex
{
	vec3 position;
	vec3 normal;
	vec2 texCoord;

	Vertex() {};
	Vertex(vec3 p, vec3 n, vec2 t)
	{
		position = p;
		normal = n;
		texCoord = t;
	}
};

struct Material
{
	char name;
	float ns, alpha, illum;
	float amb[3], dif[3], spec[3];
	unsigned int ID;
	string path;

};