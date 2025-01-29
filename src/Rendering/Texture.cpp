#include "Rendering\Texture.h"
#include <stb/stb_image.h>
#include <iostream>

std::unordered_map<std::string, Texture*> Texture::s_cache;

Texture* Texture::loadFromFile(const std::string& path, bool flipVertical)
{
	// Get logger
	Logger& logger = Logger::getInstance();

	// Check cache first
	auto it = s_cache.find(path);
	if (it != s_cache.end()) return it->second;

	// Load image data
	stbi_set_flip_vertically_on_load(flipVertical);
	int width;;
	int height;
	int channels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (!data)
	{
		logger.log("Failed to load texture: " + path + "\n");

		return nullptr;
	}

	// Determine format
	GLenum format = GL_RGB;
	switch (channels)
	{
		case 1: format = GL_RED; break;
		case 3: format = GL_RGB; break;
		case 4: format = GL_RGBA; break;
	}

	// Create OpenGL texture
	Texture* texture = new Texture();
	texture->m_path = path;
	texture->m_width = width;
	texture->m_height = height;

	glGenTextures(1, &texture->m_id);
	glBindTexture(GL_TEXTURE_2D, texture->m_id);

	// Set parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Upload data and generate mipmaps
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Cleanup
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Add to cache
	s_cache[path] = texture;
	
	return texture;
}

Texture::~Texture()
{
	if (m_id != 0)
	{
		glDeleteTextures(1, &m_id);
		m_id = 0;
	}
}

void Texture::bind(GLenum textureUnit) const
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_id);
}
