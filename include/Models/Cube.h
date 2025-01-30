#pragma once

#include <glm/glm.hpp>
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

private:
	std::vector<Vertex> m_vertices{};
	std::vector<glm::vec3> m_cubePositions{};
	unsigned int m_vao{ 0 };
	Shader* m_shader{ nullptr };
	Texture* m_texture{ nullptr };
};

