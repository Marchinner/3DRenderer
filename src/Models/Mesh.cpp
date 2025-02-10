#include "Models/Mesh.h"

#include <glad/glad.h>
#include <Rendering/Texture.h>

Mesh::Mesh(const std::vector<Vertex>& vertices)
    : m_vertices{ vertices }
{
    glGenVertexArrays(1, &m_vao);
    
    VBO vbo;
    glGenBuffers(1, &vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // texture attributes
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vao);
}

void Mesh::draw(const Shader& shader, const Texture& texture)
{
    texture.bind();
    shader.use();

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_vertices.size()));
    glBindVertexArray(0);
}
