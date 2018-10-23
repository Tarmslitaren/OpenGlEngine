#pragma once
#include <string>
#include <vector>
#include "glad/glad.h"
namespace GLEN
{

	enum CubeMapOrientation
	{
		CUBE_MAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		CUBE_MAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		CUBE_MAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		CUBE_MAP_NEAGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		CUBE_MAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		CUBE_MAP_NEAGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};
	class Texture
	{
	public:
		Texture();
		~Texture();
		bool LoadTexture(std::string path, bool transparant = false);
		bool LoadCubeMap(std::string id, std::vector< std::pair <std::string, CubeMapOrientation> > paths);
		unsigned int getHandle() { return m_handle; }
		const std::string& getPath() { return m_path; }
	private:
		int m_width;
		int m_height;
		int m_channels;
		unsigned int m_handle;
		std::string m_path;
	};
}

