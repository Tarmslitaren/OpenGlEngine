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


bool GLEN::Texture::LoadTexture(std::string path, bool flipY)
{

	m_path = path;

	glGenTextures(1, &m_handle);
	glBindTexture(GL_TEXTURE_2D, m_handle);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(flipY); //flips the coords
	
	unsigned char *data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);
	if (data)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		int format = GL_RGB;
		if (m_channels == 1)
			format = GL_RED;
		else if (m_channels == 3)
			format = GL_RGB;
		else if (m_channels == 4)//very naiive check. only works for a subset of image types.
			format = GL_RGBA;


		//todo: use stb lib to figure out type of texture and use corresponding GL type (eg: GL_RGB,GL_RGBA etc)
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data); //todo: check for errors obv.


		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		return true;
	}
	else
	{
		std::cout << "Failed to load texture: " << path.c_str() << std::endl;
		return false;
	}

}
