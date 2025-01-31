#include "Models/Cube.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube()
{
	m_shader = new Shader{ "shaders/cube.vert", "shaders/cube.frag" };
	m_texture = Texture::loadFromFile("assets/textures/container.jpg");

	m_vertices = {
{glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 0.0f}},
{glm::vec3{0.5f, -0.5f, -0.5f}, glm::vec2{1.0f, 0.0f}},
{glm::vec3{0.5f,  0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
{glm::vec3{0.5f,  0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
{glm::vec3{-0.5f,  0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
{glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 0.0f}},
{glm::vec3{-0.5f, -0.5f,  0.5f}, glm::vec2{0.0f, 0.0f}},
{glm::vec3{0.5f, -0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},
{glm::vec3{0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 1.0f}},
{glm::vec3{0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 1.0f}},
{glm::vec3{-0.5f,  0.5f,  0.5f}, glm::vec2{0.0f, 1.0f}},
{glm::vec3{-0.5f, -0.5f,  0.5f}, glm::vec2{0.0f, 0.0f}},
{glm::vec3{-0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},
{glm::vec3{-0.5f,  0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
{glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
{glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
{glm::vec3{-0.5f, -0.5f,  0.5f}, glm::vec2{0.0f, 0.0f}},
{glm::vec3{-0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},
{glm::vec3{0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},
{glm::vec3{0.5f,  0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
{glm::vec3{0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
{glm::vec3{0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
{glm::vec3{0.5f, -0.5f,  0.5f}, glm::vec2{0.0f, 0.0f}},
{glm::vec3{0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},
{glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
{glm::vec3{0.5f, -0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
{glm::vec3{0.5f, -0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},
{glm::vec3{0.5f, -0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},
{glm::vec3{-0.5f, -0.5f,  0.5f}, glm::vec2{0.0f, 0.0f}},
{glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
{glm::vec3{-0.5f,  0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
{glm::vec3{0.5f,  0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
{glm::vec3{0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},
{glm::vec3{0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},
{glm::vec3{-0.5f,  0.5f,  0.5f}, glm::vec2{0.0f, 0.0f}},
{glm::vec3{-0.5f,  0.5f, -0.5f}, glm::vec2{ 0.0f, 1.0f}}
	};

	// world space positions of our cubes
	m_cubePositions = {
		glm::vec3{0.0f,  0.0f,  0.0f},
		glm::vec3{2.0f,  5.0f, -15.0f},
		glm::vec3{-1.5f, -2.2f, -2.5f},
		glm::vec3{-3.8f, -2.0f, -12.3f},
		glm::vec3{2.4f, -0.4f, -3.5f},
		glm::vec3{-1.7f,  3.0f, -7.5f},
		glm::vec3{1.3f, -2.0f, -2.5f},
		glm::vec3{1.5f,  2.0f, -2.5f},
		glm::vec3{1.5f,  0.2f, -1.5f},
		glm::vec3{-1.3f,  1.0f, -1.5f}
	};

	glGenVertexArrays(1, &m_vao);
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

	// position attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// texture attributes
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
	glEnableVertexAttribArray(1);

	glBindVertexArray(1);

	m_shader->use();
	m_shader->setInt("texture1", 0);
}

Cube::~Cube()
{
	glDeleteVertexArrays(1, &m_vao);
}

void Cube::draw() const
{
	//// model
	//glm::mat4 model = glm::mat4{ 1.0f };
	//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3{ 0.5f, 1.0f, 0.0f });


	//// view
	//glm::mat4 view = glm::mat4{ 1.0f };
	//view = glm::translate(view, glm::vec3{ 0.0f, 0.0f, -3.0f });

	m_texture->bind();
	m_shader->use();

	glUniformMatrix4fv(glGetUniformLocation(m_shader->getId(), "view"), 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_shader->getId(), "projection"), 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

	glBindVertexArray(m_vao);
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4{ 1.0f };
		model = glm::translate(model, m_cubePositions[i]);	
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3{ 1.0f, 0.3f, 0.5f });
		glUniformMatrix4fv(glGetUniformLocation(m_shader->getId(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_vertices.size()));
	}
	glBindVertexArray(0);
}

glm::mat4& Cube::getViewMatrix()
{
	return m_viewMatrix;
}

glm::mat4& Cube::getProjectionMatrix()
{
	return m_projectionMatrix;
}
