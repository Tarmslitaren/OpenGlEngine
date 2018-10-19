#include "Material.h"
#include "Engine.h"
#include "ShaderProgram.h"
using namespace GLEN;

Material::Material()
{
}


Material::~Material()
{
}

void GLEN::Material::InitShaderVariables()
{
	//does this need to be run per frame? to set different materials with same shader
	ShaderProgram shader = *Engine::GetInstance()->GetShaderContainer().GetShaderProgram(m_shaderHandle);
	if (m_diffuseTextureHandles.size() > 0) {
		for (unsigned int i = 0; i < m_diffuseTextureHandles.size(); i++)
		{
			shader.setInt("material.diffuse[" + std::to_string(i) + "]", m_diffuseTextureHandles[i].second);
		}
		
	}
	else
	{
		shader.setVector("material.diffuse", m_diffuseColor);
	}
	if (m_specularTextureHandles.size() > 0) {
		for (unsigned int i = 0; i < m_specularTextureHandles.size(); i++)
		{
			shader.setInt("material.specular[" + std::to_string(i) + "]", m_specularTextureHandles[i].second);
		}
	}
	else
	{
		shader.setVector("material.specular", m_specularColor);
	}
	shader.setVector("material.ambient", m_ambient);
	shader.setFloat("material.shininess", m_shininess);
	shader.setInt("material.nrOfDiffuse", m_diffuseTextureHandles.size());
	shader.setInt("material.nrOfSpecular", m_specularTextureHandles.size());
}

void GLEN::Material::Render()
{

	//glBindTexture(GL_TEXTURE_2D, 0); //need this to reset?

	for (auto handles : m_diffuseTextureHandles)
	{
		glActiveTexture(GL_TEXTURE0 + handles.second); // activate proper texture unit before binding
		glBindTexture(GL_TEXTURE_2D, handles.first);
	}
	for (auto handles : m_specularTextureHandles)
	{
		glActiveTexture(GL_TEXTURE0 + handles.second); // activate proper texture unit before binding
		glBindTexture(GL_TEXTURE_2D, handles.first);
	}
	//InitShaderVariables(); //needed?

	//glActiveTexture(GL_TEXTURE0);
}

void GLEN::Material::AddDiffuseTexture(std::string path, int binding, bool transparant)
{
	int textureHandle = Engine::GetInstance()->GetTextureContainer().GetTexture(path, transparant)->getHandle();
	m_diffuseTextureHandles.push_back({ textureHandle, binding });
}

void GLEN::Material::AddSpecularTexture(std::string path, int binding)
{
	int textureHandle = Engine::GetInstance()->GetTextureContainer().GetTexture(path)->getHandle();
	m_specularTextureHandles.push_back({ textureHandle, binding });
}
