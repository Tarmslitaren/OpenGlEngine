#pragma once
#include <string>
namespace GLEN
{
	class Texture
	{
	public:
		Texture();
		~Texture();
		bool LoadTexture(std::string path, bool transparant = false);
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

