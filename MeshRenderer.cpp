#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture)
	: m_mesh(mesh)
	, m_texture(texture)
{
}

void MeshRenderer::OnRender()
{
	if (m_texture)
		m_texture->Bind();

	if (m_mesh)
		m_mesh->Draw();
}
