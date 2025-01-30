#pragma once
#include <Rendering/Shader.h>
#include <glm/glm.hpp>
#include <vector>
#include <Rendering/Texture.h>


class Triangle
{
public:

	struct Vertex {
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texture;
	};

	Triangle();
	~Triangle();

	void draw() const;
private:
	std::vector<Vertex> m_vertex;
	unsigned int m_vao;
	Shader* m_shader;
	Texture* m_texture;
};

