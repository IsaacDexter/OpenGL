#ifndef ACTOR_H
#define ACTOR_H

#include "stdafx.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "MeshRenderer.h";
#include <string>

class Actor
{
public:
	Actor(std::string name, std::shared_ptr<MeshRenderer> meshRenderer, GLuint modelLocation);

	virtual void Update(const float deltaTime) {}
	virtual void Draw();

	glm::vec3 GetPosition() const { return m_position; }
	glm::vec3 GetRotation() const { return m_rotation; }
	glm::vec3 GetScale() const { return m_scale; }

	glm::mat4 GetModel() const { return m_model; }
	
	std::string GetName() const { return m_name; }

	void SetPosition(const glm::vec3 position) { m_position = position; UpdateModel(); }
	void SetRotation(const glm::vec3 rotation) { m_rotation = rotation; UpdateModel(); }
	void SetScale(const glm::vec3 scale) { m_scale = scale; UpdateModel(); }

	void SetName(const std::string name) { m_name = name; }
protected:
	void UpdateModel();

	// The actor's transformations that make up its model matrix
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	// The actor's model matrix, to be set as part of the MVP matrix
	glm::mat4 m_model;
	// The location of the model matrix uniform in the shader, to be updated with this' model
	const GLuint m_modelLocation;

	// The actor's name identifier for the scene
	std::string m_name;

	// Pointers to the actor's mesh and texture
	std::shared_ptr<MeshRenderer> m_meshRenderer;
};


#endif // !ACTOR_H