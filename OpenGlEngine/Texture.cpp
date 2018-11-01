#include "Texture.h"
#include "stb_image.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "ErrorHandler.h"
using namespace GLEN;


Texture::Texture()
{
}


Texture::~Texture()
{
}


bool GLEN::Texture::LoadTexture(std::string path, bool gammaCorrect, bool transparant)
{

	m_path = path;

	glGenTextures(1, &m_handle);
	glBindTexture(GL_TEXTURE_2D, m_handle);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	
	unsigned char *data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);
	if (data)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		int format, format2;
		GetFormats(m_channels, format, format2, gammaCorrect);
		
		if (m_channels == 4)
		{
			if (transparant)
			{
				//don't wrap if has alpha: may produce blending artifacts so clamp instead.
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
		}


		//todo: use stb lib to figure out type of texture and use corresponding GL type (eg: GL_RGB,GL_RGBA etc)
		glTexImage2D(GL_TEXTURE_2D, 0, format2, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data); //todo: check for errors obv.


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


bool GLEN::Texture::LoadCubeMap(std::string id, std::vector<std::pair<std::string, CubeMapOrientation>> paths, bool gammaCorrect)
{

	m_path = id;

	glGenTextures(1, &m_handle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	for (auto image : paths)
	{
		unsigned char *data = stbi_load(image.first.c_str(), &m_width, &m_height, &m_channels, 0);
		if (data)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


			int format, format2;
			GetFormats(m_channels, format, format2, gammaCorrect);;
			//todo: use stb lib to figure out type of texture and use corresponding GL type (eg: GL_RGB,GL_RGBA etc)
			glTexImage2D(image.second, 0, format2, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data); //todo: check for errors obv.

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << image.first.c_str() << std::endl;
			return false;
		}
	}
	return true;
}

void GLEN::Texture::GetFormats(int channels, int & format, int & format2, bool gammaCorrect)
{

	format = GL_RGB;
	format2 = GL_RGB;
	if (m_channels == 1)
	{
		format = GL_RED;
		format2 = GL_RED;
	}
	else if (m_channels == 3)
	{
		format = GL_RGB;
		if (gammaCorrect)
		{
			format2 = GL_SRGB;
		}
	}
	else if (m_channels == 4)//very naiive check. only works for a subset of image types.
	{
		format = GL_RGBA;
		if (gammaCorrect)
		{
			format2 = GL_SRGB_ALPHA;
		}
	}
	//format2 = format;
}
