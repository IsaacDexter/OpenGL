#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H


#include "Component.h"
#include "stdafx.h"
#include "Mesh.h"
#include "Texture.h"

class MeshRenderer :
    public Component
{
public:
    MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture);

    virtual void OnRender() override;
private:
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Texture> m_texture;
};


#endif // !MESH_RENDERER_H