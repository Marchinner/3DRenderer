#include "Models/Triangle.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

Triangle::Triangle()
	: m_vertex{}
	, m_vao{ 0 }
	, m_shader{ nullptr }
{
	m_shader = new Shader("assets/shaders/triangle.vert", "assets/shaders/triangle.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	m_vertex = {
		{glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f}},
		{glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}},
		{glm::vec3{0.0f,  0.5f, 0.0f},  glm::vec3{0.0f, 0.0f, 1.0f}}
	};

	unsigned int VBO;
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertex.size() * sizeof(Vertex), &m_vertex[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

Triangle::~Triangle()
{
	glDeleteVertexArrays(1, &m_vao);
}

void Triangle::draw() const
{
	m_shader->use();
	int sVertex = static_cast<int>(m_vertex.size());
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_vertex.size()));
}
