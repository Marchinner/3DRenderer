#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <Rendering/Texture.h>
#include "Rendering/Shader.h"


class Rectangle
{
public:

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texture;
	};

	Rectangle();
	~Rectangle();

	void draw() const;

private:
	std::vector<Vertex> m_vertices{};
	std::vector<unsigned int> m_indices{};
	unsigned int m_vao{ 0 };
	Shader* m_shader{ nullptr };
	Texture* m_texture{ nullptr };
	Texture* m_texture2{ nullptr };

};

