#pragma once
#include "Texture.h"
#include <vector>
namespace GLEN
{
	class TextureContainer
	{
	public:
		TextureContainer();
		~TextureContainer();
		Texture* GetTexture(std::string path, bool transparant = false);

	private:
		std::vector<Texture*> m_textures;
	};
}

