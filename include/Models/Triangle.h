#pragma once
#include <Rendering/Shader.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
};

class Triangle
{
public:
	Triangle();
	~Triangle();

	void draw() const;
private:
	std::vector<Vertex> m_vertex;
	unsigned int m_vao;
	Shader* m_shader;
};

