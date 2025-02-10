#pragma once

#include "Mesh.h"
#include "Rendering/Texture.h"

#include <vector>

class Model
{
public:
    Model(std::vector<Mesh>& meshes);
    ~Model();

    void draw(const Shader& shader, const Texture& texture);
private:
    std::vector<Mesh> m_meshes;
};

