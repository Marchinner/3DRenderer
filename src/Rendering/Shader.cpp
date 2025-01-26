#include "Rendering/Shader.h"
#include "Utils/FileUtils.h"
#include "Utils/Logger.h"

#include <glad/glad.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
	: m_logger{ Logger::getInstance() }
{
	std::string vertexCode;
	std::string fragmentCode;

	if (FileUtils::fileExists(vertexPath))
	{
		vertexCode = FileUtils::readAsString(vertexPath);
	}

	if (FileUtils::fileExists(fragmentPath))
	{
		fragmentCode = FileUtils::readAsString(fragmentPath);
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// Compile the shaders
	unsigned int vertex;
	unsigned int fragment;

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkShaderCompileErrors(vertex, Type::Vertex);

	// Fragment
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkShaderCompileErrors(fragment, Type::Fragment);

	// Shader Program
	m_id = glCreateProgram();
	glAttachShader(m_id, vertex);
	glAttachShader(m_id, fragment);
	glLinkProgram(m_id);
	checkProgramLinkingErrors(m_id);

	// Clear data
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(m_id);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::checkShaderCompileErrors(unsigned int shader, Type type) const
{
	std::string shaderType;
	switch (type)
	{
	case Shader::Type::Vertex:
		shaderType = "VERTEX";
		break;
	case Shader::Type::Fragment:
		shaderType = "FRAGMENT";
		break;
	default:
		shaderType = "UNKNOWN";
		break;
	}
	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		m_logger.log("ERROR::SHADER::" + shaderType + "::COMPILATION FAILED!",
			Logger::Level::Error);
	}
}

void Shader::checkProgramLinkingErrors(unsigned int program) const
{
	int success;
	char infoLog[512];
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_id, 512, NULL, infoLog);
		m_logger.log("ERROR::SHADER::PROGRAM::LINKING FAILED", Logger::Level::Error);
	}
}
