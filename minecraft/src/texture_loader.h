#pragma once

#include <GLEW/glew.h>
#include "stb_image.h"

namespace TextureLoader {
	unsigned int load(const char* path, unsigned int n) 
	{
		unsigned int m_id;
		glGenTextures(1, &m_id);
		glActiveTexture(GL_TEXTURE0 + n);
		glBindTexture(GL_TEXTURE_2D, m_id);
		
		int width, height, nrChannels;
		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);

		return m_id;
	}
};