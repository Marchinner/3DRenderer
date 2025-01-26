#pragma once

#include <string>

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

private:
	void checkShaderCompileErrors(unsigned int shader, Type shaderType) const;
	void checkProgramLinkingErrors(unsigned int program) const;

private:
	Logger& m_logger;
	unsigned int m_id;
};

