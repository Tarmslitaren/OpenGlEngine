#pragma once
#include "Texture.h"
#include <vector>
#include "CU_Vector.h"
namespace GLEN
{
	class Material
	{
	public:
		Material();
		~Material();
		void InitShaderVariables();
		void Render();
		void AddDiffuseTexture(std::string path, int binding);
		void AddSpecularTexture(std::string path, int binding);
		void SetAmbient(const CU::Vector3f ambient) { m_ambient = ambient; }
		void SetDiffuse(const CU::Vector3f diffuse) { m_diffuseColor = diffuse; }
		void SetSpecular(const CU::Vector3f specular) { m_specularColor = specular; }
		void SetShininess(float shininess) { m_shininess = shininess; }
		void SetShader(int handle) { m_shaderHandle = handle; }
	private:
		CU::Vector3f m_ambient = { 0.1f, 0.1f ,0.1f }; //usually not used if has diffuse texture
		CU::Vector3f m_diffuseColor;					//not used if has diffusetexture
		CU::Vector3f m_specularColor = { 1, 1, 1 };		//usually 1. Not used if has specular texture map
		float m_shininess = 32.f;								//multiplier for specular map
		//int m_diffuseTextureHandle = -1;
		//int m_specularTextureHandle = -1;
		std::vector<std::pair<int, int> > m_diffuseTextureHandles;
		std::vector<std::pair<int, int>> m_specularTextureHandles;
		//int m_diffuseBinding = 0;
		//int m_specularBinding = 1;
		int m_shaderHandle;
	};
}

