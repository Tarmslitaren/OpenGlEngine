#include "Texture.h"
#include "stb_image.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
using namespace GLEN;


Texture::Texture()
{
}


Texture::~Texture()
{
}

void GLEN::Texture::LoadTexture(std::string path)
{
	glGenTextures(1, &m_handle);
	glBindTexture(GL_TEXTURE_2D, m_handle);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *data = stbi_load("container.jpg", &m_width, &m_height, &m_channels, 0);
	if (data)
	{
		//todo: use stb lib to figure out type of texture and use corresponding GL type (eg: GL_RGB,GL_RGBA etc)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

}
