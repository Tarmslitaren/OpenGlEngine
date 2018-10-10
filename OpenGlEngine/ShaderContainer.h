#pragma once
#include "ShaderProgram.h"
#include <vector>
namespace GLEN
{
	class ShaderContainer
	{
	public:
		ShaderContainer();
		~ShaderContainer();
		ShaderProgram* GetShaderProgram(int handle);
		ShaderProgram* GetShaderProgram(std::string id);
		ShaderProgram* CreateShaderProgram(std::string id, std::string vertexShader, std::string fragmentShader);
	private:
		std::vector<ShaderProgram*> m_shaders;
	};
}

