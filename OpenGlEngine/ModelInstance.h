#pragma once
#include "Primitive.h"
#include "CU_Matrix.h"
#include "CU_Vector.h"
#include "ShaderProgram.h"
#include <string>
namespace GLEN
{
	class Light;
	class ModelInstance
	{
	public:
		ModelInstance(std::string primitiveId, std::string shaderProgram);
		~ModelInstance();
		void Render(Light* light);
		void SetOrientation(const CU::Matrix33f& orientation) { m_orientation = orientation; }
		void SetPosition(const CU::Vector3f& position) { m_position = position; }
		void SetToRender(bool toRender) { m_isToRender = toRender; }
		bool GetVisible() { return m_isToRender; }
		void SetScale(float value) { m_orientation.Scale(value); } //let's see if this works
	private:
		bool m_isToRender = true;
		Primitive* m_primitive;
		CU::Matrix33f m_orientation;
		CU::Vector3f m_position;
		std::string m_shaderId;
	};
}

