#include "Actor.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

/// <summary>
/// Create an actor, which encapsulates mesh, texture and transform
/// </summary>
/// <param name="name">name of the actor in the scene</param>
/// <param name="mesh">ptr to the mesh</param>
/// <param name="texture">ptr to the texture</param>
/// <param name="modelLocation">glGetUniformLocation(m_shader->GetProgram(), "uModel");</param>
Actor::Actor(std::string name, std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture, GLuint modelLocation)
	: m_name(name)
	, m_mesh(mesh)
	, m_texture(texture)
	, m_modelLocation(modelLocation)
	, m_model(glm::mat4(1.0f))
	, m_position(0.0f)
	, m_rotation(0.0f)
	, m_scale(1.0f)
{
	UpdateModel();
}

void Actor::Draw()
{
	// Update the model matrix 
	glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_model));

	if (m_texture)
		m_texture->Bind();

	if (m_mesh)
		m_mesh->Draw();
}

/// <summary>
/// Update the actors model matrix based on translation (position), rotation (orientation), scale (scale).
/// </summary>
void Actor::UpdateModel()
{
	// Translate
	glm::mat4 translation = glm::mat4(1.0f);
	translation = glm::translate(translation, m_position);

	// Rotate by each axis
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation = glm::rotate(rotation, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotation = glm::rotate(rotation, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotation = glm::rotate(rotation, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	// Scale
	glm::mat4 scale = glm::mat4(1.0f);
	scale = glm::scale(scale, m_scale);

	m_model = translation * rotation * scale;
}
