#ifndef TEX_H
#define TEX_H

#include "src/stb_image.h"

class Tex {
private:
	unsigned int m_id;
public:
	Tex(const char* path, unsigned int n)
	{
		m_id = createTexture(GL_TEXTURE_2D, n);
		int width, height, nrChannels;
		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	unsigned int createTexture(GLenum target, unsigned int n)
	{
		unsigned int texture;
		glGenTextures(1, &texture);
		glActiveTexture(GL_TEXTURE0 + n);
		glBindTexture(target, texture);
		return texture;
	}
};

#endif