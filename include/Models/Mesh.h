#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <Rendering/Shader.h>
#include <Rendering/Texture.h>

typedef unsigned int VAO;
typedef unsigned int VBO;
typedef unsigned int EBO;

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texture;
};

class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices);
    ~Mesh();

    void draw(const Shader& shader, const Texture& texture);

private:

private:
    VAO m_vao{ 0 };
    std::vector<Vertex> m_vertices;
};

