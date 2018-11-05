#pragma once
#include "CU_Vector.h"
#include <string>
#include "ModelInstance.h"
#include "Converters.h"
namespace GLEN
{
	//attenuation table for a somewhat realistic point light
	/*
	Distance	Constant	Linear	Quadratic
		7		1.0			0.7		1.8
		13		1.0			0.35	0.44
		20		1.0			0.22	0.20
		32		1.0			0.14	0.07
		50		1.0			0.09	0.032
		65		1.0			0.07	0.017
		100		1.0			0.045	0.0075
		160		1.0			0.027	0.0028
		200		1.0			0.022	0.0019
		325		1.0			0.014	0.0007
		600		1.0			0.007	0.0002
		3250	1.0			0.0014	0.000007
*/
	enum LightType
	{
		DIRECTIONAL_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT
	};

	class Light
	{
	public:
		Light(LightType lightType = POINT_LIGHT, ModelInstance* instance = nullptr, int index = -1);
		~Light();
		void SetPosition(const CU::Vector3f& pos) { m_position = pos; }
		void SetDirection(const CU::Vector3f& dir) { m_direction = dir; }
		void SetDiffuse(const CU::Vector3f& diffuse) { m_diffuse = diffuse; }
		void SetSpecular(const CU::Vector3f& specular) { m_specular = specular; }
		void SetAmbient(const CU::Vector3f& ambient) { m_ambient = ambient; }
		void SetAttenuation(float linear, float quadratic, float constant = 1);
		void SetSpotlightRadius(float radius, float outerRadius);
		const CU::Vector3f& GetPosition() const { return m_position; }
		const CU::Vector3f& GetDirection() const { return m_direction; }
		//const CU::Vector3f& GetDiffuse() const { return m_diffuse; }
		//const CU::Vector3f& GetSpecular() const { return m_specular; }
		//const CU::Vector3f& GetAmbient() const { return m_ambient;}
		void RenderObject();
		void ApplytoShader(std::string shader);
		LightType GetType() { return m_type; }
	private:
		LightType m_type;
		ModelInstance* m_debugRenderObject;
		CU::Vector3f m_position;
		CU::Vector3f m_direction;
		CU::Vector3f m_diffuse;
		CU::Vector3f m_specular;
		CU::Vector3f m_ambient;

		//attenuation
		float m_constant = 1;
		float m_linear = 0.7f;
		float m_quadratic = 0.18f;
		float m_spotlightRadius = 0;
		float m_spotlightRadiusOuter = 0;

		//index to point lite array (need to change this idea somehow)
		int m_index = -1;


	};
}

