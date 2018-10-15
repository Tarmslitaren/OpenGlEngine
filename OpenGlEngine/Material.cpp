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
	ShaderProgram shader = *Engine::GetInstance()->GetShaderContainer().GetShaderProgram(m_shaderHandle);
	if (m_diffuseTextureHandle != -1) {
		shader.setInt("material.diffuse", m_diffuseBinding);
	}
	else
	{
		shader.setVector("material.diffuse", m_diffuseColor);
	}
	if (m_specularTextureHandle != -1) {
		shader.setInt("material.specular", m_specularBinding);
	}
	else
	{
		shader.setVector("material.specular", m_specularColor);
	}
	shader.setVector("material.ambient", m_ambient);
	shader.setFloat("material.shininess", m_shininess);
}

void GLEN::Material::Render()
{

	glActiveTexture(GL_TEXTURE0 + m_diffuseBinding);
	glBindTexture(GL_TEXTURE_2D, m_diffuseTextureHandle);

	glActiveTexture(GL_TEXTURE0 + m_specularBinding);
	glBindTexture(GL_TEXTURE_2D, m_specularTextureHandle);
	
	//glBindTexture(GL_TEXTURE_2D, 0); //need this to reset?
}

void GLEN::Material::SetDiffuseTexture(std::string path, int binding)
{
	m_diffuseBinding = binding;
	m_diffuseTextureHandle = Engine::GetInstance()->GetTextureContainer().GetTexture(path)->getHandle();
}

void GLEN::Material::SetSpecularTexture(std::string path, int binding)
{
	m_specularTextureHandle = Engine::GetInstance()->GetTextureContainer().GetTexture(path)->getHandle();
	m_specularBinding = binding;
}
