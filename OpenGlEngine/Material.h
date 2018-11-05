#pragma once
#include "Texture.h"
#include <vector>
#include "CU_Vector.h"
#include "CU_Matrix.h"
#include <string>
#include "ShaderProgram.h"
namespace GLEN
{
	class Material
	{
	public:
		Material(std::string shader);
		~Material();
		void InitShaderVariables();
		void Render(const CU::Matrix44f& model, std::string overrideShader = "");
		void Render();
		void AddDiffuseTexture(std::string path, int binding, bool transparant = false);
		void AddDiffuseTexture(int textureHandle, int binding);
		void SetCubeMapTexture(std::string id);
		void AddSpecularTexture(std::string path, int binding);
		void SetAmbient(const CU::Vector3f ambient) { m_ambient = ambient; }
		void SetDiffuse(const CU::Vector3f diffuse) { m_diffuseColor = diffuse; }
		void SetSpecular(const CU::Vector3f specular) { m_specularColor = specular; }
		void SetShininess(float shininess) { m_shininess = shininess; }
		void SetShader(ShaderProgram* shader) { m_shader = shader; }
	private:
		void RenderInternal();
		CU::Vector3f m_ambient = { 0.1f, 0.1f ,0.1f }; //usually not used if has diffuse texture
		CU::Vector3f m_diffuseColor;					//not used if has diffusetexture
		CU::Vector3f m_specularColor = { 1, 1, 1 };		//usually 1. Not used if has specular texture map
		float m_shininess = 64.f;								//multiplier for specular map
		std::vector<std::pair<int, int> > m_diffuseTextureHandles;
		std::vector<std::pair<int, int>> m_specularTextureHandles;
		int m_cubeMapHandle = -1;
		ShaderProgram* m_shader;
	};
}

