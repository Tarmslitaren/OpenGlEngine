#include "Material.h"
#include "Engine.h"
#include "ShaderProgram.h"
#include "ErrorHandler.h"
using namespace GLEN;

Material::Material(std::string shader)
{
	m_shader = Engine::GetInstance()->GetShaderContainer().GetShaderProgram(shader);
}


Material::~Material()
{
}

void GLEN::Material::InitShaderVariables()
{
	ErrorHandler::CheckError("InitShaderVariables start");
	//does this need to be run per frame? to set different materials with same shader
	if (m_diffuseTextureHandles.size() > 0) {
		for (unsigned int i = 0; i < m_diffuseTextureHandles.size(); i++)
		{
			m_shader->setInt("material.diffuse[" + std::to_string(i) + "]", m_diffuseTextureHandles[i].second);
		}
		ErrorHandler::CheckError("InitShaderVariables 1");
	}
	else
	{
		//m_shader->setVector("material.diffuse", m_diffuseColor);
	}
	if (m_specularTextureHandles.size() > 0) {
		for (unsigned int i = 0; i < m_specularTextureHandles.size(); i++)
		{
			m_shader->setInt("material.specular[" + std::to_string(i) + "]", m_specularTextureHandles[i].second);
		}
	}
	else
	{
		//m_shader->setVector("material.specular", m_specularColor); //this produce error when material.specular is not a vec3
	}
	m_shader->setVector("material.ambient", m_ambient);
	m_shader->setFloat("material.shininess", m_shininess);
	m_shader->setInt("material.nrOfDiffuse", m_diffuseTextureHandles.size());
	m_shader->setInt("material.nrOfSpecular", m_specularTextureHandles.size());
	ErrorHandler::CheckError("InitShaderVariables end");
}

void GLEN::Material::Render(const CU::Matrix44f& model, std::string overrideShader)
{
	ShaderProgram* original = m_shader;
	if (overrideShader.size() > 0)
	{
		m_shader = Engine::GetInstance()->GetShaderContainer().GetShaderProgram(overrideShader);
	}
	RenderInternal();

	//todo: I've made a horrible mistake! in marrying materials to meshes, made it difficult to easily create new instances with different shaders.
	//update shader vars from model instance
	Camera cam = Engine::GetInstance()->GetCamera();

	m_shader->setMatrix("model", model);

	m_shader->setVector("viewPos", cam.GetPosition());

	m_shader = original;
}

void GLEN::Material::Render()
{
	RenderInternal();
}

void GLEN::Material::AddDiffuseTexture(std::string path, int binding, bool transparant)
{
	int textureHandle = Engine::GetInstance()->GetTextureContainer().GetTexture(path, transparant)->getHandle();
	m_diffuseTextureHandles.push_back({ textureHandle, binding });
}

void GLEN::Material::AddDiffuseTexture(int textureHandle, int binding, bool transparant)
{
	m_diffuseTextureHandles.push_back({ textureHandle, binding });
}

void GLEN::Material::SetCubeMapTexture(std::string id)
{
	m_cubeMapHandle = Engine::GetInstance()->GetTextureContainer().GetTexture(id)->getHandle();
}

void GLEN::Material::AddSpecularTexture(std::string path, int binding)
{
	int textureHandle = Engine::GetInstance()->GetTextureContainer().GetTexture(path)->getHandle();
	m_specularTextureHandles.push_back({ textureHandle, binding });
}

void GLEN::Material::RenderInternal()
{
	m_shader->use();
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
	if (m_cubeMapHandle != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMapHandle);
		//return; //cubemaps handle their own uniforms
	}
	//InitShaderVariables(); //needed? Only if the material changes in runtime. seems to be quite specific case (unlike light properties)



	//glActiveTexture(GL_TEXTURE0);
}
