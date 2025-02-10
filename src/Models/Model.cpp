#include "Models/Model.h"
#include <Rendering/Texture.h>

Model::Model(std::vector<Mesh>& meshes)
    : m_meshes{ meshes }
{
}

Model::~Model()
{
}

void Model::draw(const Shader& shader, const Texture& texture)
{
    for (auto& mesh : m_meshes)
    {
        mesh.draw(shader, texture);
    }
}
