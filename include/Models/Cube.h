#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <Rendering/Texture.h>
#include "Rendering/Shader.h"

class Cube
{
public:

	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 texture;
	};

	Cube();
	~Cube();

	void draw() const;

	glm::mat4& getViewMatrix();
	glm::mat4& getProjectionMatrix();

private:
	std::vector<Vertex> m_vertices{};
	std::vector<glm::vec3> m_cubePositions{};
	unsigned int m_vao{ 0 };
	Shader* m_shader{ nullptr };
	Texture* m_texture{ nullptr };
	glm::mat4 m_projectionMatrix{ glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f) };
	glm::mat4 m_viewMatrix{};
};

