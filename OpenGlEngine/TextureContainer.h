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
		Texture* LoadCubeMap(std::string id, std::vector< std::pair < std::string, CubeMapOrientation > > paths);

	private:
		std::vector<Texture*> m_textures;
	};
}

