#include "TextureContainer.h"
#include "Texture.h"
//#include "CommonMacros.h"
using namespace GLEN;


TextureContainer::TextureContainer()
{
}


TextureContainer::~TextureContainer()
{
	for (Texture* texture : m_textures)
	{
		//SAFE_DELETE(texture);
	}
}

Texture* GLEN::TextureContainer::GetTexture(std::string path, bool transparant)
{
	for (Texture* texture : m_textures)
	{
		if (texture->getPath() == path)
		{
			return texture;
		}
	}
	Texture* texture = new Texture();
	if (texture->LoadTexture(path, transparant))
	{
		m_textures.push_back(texture);
		return texture;
	}
	else
	{
		//handle load failure
	}
	return nullptr;
}

Texture * GLEN::TextureContainer::LoadCubeMap(std::string id, std::vector<std::pair<std::string, CubeMapOrientation>> paths)
{
	for (Texture* texture : m_textures)
	{
		if (texture->getPath() == id)
		{
			return texture;
		}
	}
	Texture* texture = new Texture();
	if (texture->LoadCubeMap(id, paths))
	{
		m_textures.push_back(texture);
		return texture;
	}
	else
	{
		//handle load failure
	}
	return nullptr;
}
