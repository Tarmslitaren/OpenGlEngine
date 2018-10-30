#include "ShaderContainer.h"
using namespace GLEN;


ShaderContainer::ShaderContainer()
{
}


ShaderContainer::~ShaderContainer()
{
}

ShaderProgram * GLEN::ShaderContainer::GetShaderProgram(int handle)
{
	for (ShaderProgram* shaderProgram : m_shaders)
	{
		if (shaderProgram->GetHandle() == handle)
		{
			return shaderProgram;
		}
	}

	//handle error
	return nullptr;
}

ShaderProgram * GLEN::ShaderContainer::GetShaderProgram(std::string id)
{
	for (ShaderProgram* shaderProgram : m_shaders)
	{
		if (shaderProgram->GetId() == id)
		{
			return shaderProgram;
		}
	}
	return nullptr;
}

ShaderProgram * GLEN::ShaderContainer::CreateShaderProgram(std::string id, std::string vertexShader, std::string fragmentShader, std::string geometryShader)
{
	for (ShaderProgram* shaderProgram : m_shaders) //sanity check
	{
		if (shaderProgram->GetId() == id)
		{
			return shaderProgram;
		}
	}
	GLEN::ShaderProgram* shaderProgram = new ShaderProgram(id, vertexShader, fragmentShader, geometryShader);
	m_shaders.push_back(shaderProgram);
	return shaderProgram;
}
