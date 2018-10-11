#pragma once
#include "CU_Vector.h"
#include <string>
#include "ModelInstance.h"
namespace GLEN
{
	class Light
	{
	public:
		Light(ModelInstance* instance = nullptr);
		~Light();
		void SetPosition(const CU::Vector3f& pos) { m_position = pos; }
		void SetDiffuse(const CU::Vector3f& diffuse) { m_diffuse = diffuse; }
		void SetSpecular(const CU::Vector3f& specular) { m_specular = specular; }
		void SetAmbient(const CU::Vector3f& ambient) { m_ambient = ambient; }
		const CU::Vector3f& GetPosition() const { return m_position; }
		const CU::Vector3f& GetDiffuse() const { return m_diffuse; }
		const CU::Vector3f& GetSpecular() const { return m_specular; }
		const CU::Vector3f& GetAmbient() const { return m_ambient;}
		void RenderObject();
	private:
		ModelInstance* m_debugRenderObject;
		CU::Vector3f m_position;
		CU::Vector3f m_diffuse;
		CU::Vector3f m_specular;
		CU::Vector3f m_ambient;


	};
}

