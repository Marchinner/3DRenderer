#pragma once

#include <Utils/Logger.h>
#include <glad/glad.h>
#include <string>
#include <unordered_map>

class Texture
{
public:
	// Load texture from file (with caching)
	static Texture* loadFromFile(const std::string& path, bool flipVertical = true);

	~Texture();

	// Bind to a texture unit
	void bind(GLenum textureUnit = GL_TEXTURE0) const;

	// Getters
	GLuint getID() const { return m_id; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

	// Disallow copying
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

private:
	Texture() = default; // Private constructor for static creation

	GLuint m_id = 0;
	int m_width = 0;
	int m_height = 0;
	std::string m_path;

	// Cache to avoid reloading the same texture
	static std::unordered_map<std::string, Texture*> s_cache;
};

