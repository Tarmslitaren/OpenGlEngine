#pragma once
#include <string>
namespace GLEN
{
	class Texture
	{
	public:
		Texture();
		~Texture();
		void LoadTexture(std::string path, bool flipY = true);
		unsigned int getHandle() { return m_handle; }
	private:
		int m_width;
		int m_height;
		int m_channels;
		unsigned int m_handle;
	};
}

