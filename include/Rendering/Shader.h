#pragma once

#include <string>
#include <glm/glm.hpp>

class Logger;

class Shader
{
public:
	enum class Type
	{
		Vertex,
		Fragment
	};

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setMat4(const std::string& name, const glm::mat4& value) const;
	unsigned int getId() const;
private:
	void checkShaderCompileErrors(unsigned int shader, Type shaderType) const;
	void checkProgramLinkingErrors(unsigned int program) const;

private:
	Logger& m_logger;
	unsigned int m_id;
};

