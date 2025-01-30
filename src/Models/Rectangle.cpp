#include "Models/Rectangle.h"

Rectangle::Rectangle()
{
	m_shader = new Shader{ "assets/shaders/rectangle.vert", "assets/shaders/rectangle.frag" };
	m_texture = Texture::loadFromFile("assets/textures/container.jpg");
	m_texture2 = Texture::loadFromFile("assets/textures/awesomeface.png");
	m_vertices = {
		{glm::vec3{0.5f, 0.5f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f}, glm::vec2{1.0f, 1.0f}},
		{glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec2{1.0f, 0.0f}},
		{glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec2{0.0f, 0.0f}},
		{glm::vec3{-0.5f, 0.5f, 0.0f}, glm::vec3{1.0f, 1.0f, 0.0f}, glm::vec2{0.0f, 1.0f}}
	};

	m_indices = { 0, 1, 3, 1, 2, 3};

	glGenVertexArrays(1, &m_vao);
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(Vertex), &m_indices[0], GL_STATIC_DRAW);

	// position attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// color attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	// texture attributes
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

Rectangle::~Rectangle()
{
	glDeleteVertexArrays(1, &m_vao);
}

void Rectangle::draw() const
{
	m_shader->use();
	m_texture->bind();
	glUniform1i(glGetUniformLocation(m_shader->getId(), "texture2"), 1);
	m_texture2->bind(GL_TEXTURE1);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
