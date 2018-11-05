#pragma once
#include "Model.h"
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
		ModelInstance(std::string primitiveId);
		~ModelInstance();
		void Render();
		void Render(std::string shaderOverride);
		void RenderNormals();
		void SetOrientation(const CU::Matrix33f& orientation) { m_orientation = orientation; }
		void SetPosition(const CU::Vector3f& position) { m_position = position; }
		void SetToRender(bool toRender) { m_isToRender = toRender; }
		bool GetVisible() { return m_isToRender; }
		void SetScale(float value) { m_orientation.Scale(value); } //let's see if this works
		void SetOutline(float thickness = 0.1f, CU::Vector4f color = { 1,1,1,1 });
		CU::Vector3f GetPosition() { return m_position; }
		void SetRendeMode(RenderMode rendermode) { m_renderMode = rendermode; }
		std::string GetModelId() { return m_model->GetId(); }
		void GetModelMatrix(CU::Matrix44f& out);
		bool GetIsStaic() { return m_isStatic; }
		void SetStatic(bool isStatic) { m_isStatic = isStatic; }
	private:
		void DrawOutline();
		bool m_isToRender = true;
		bool m_isStatic = false;
		Model* m_model;
		CU::Matrix33f m_orientation;
		CU::Vector3f m_position;
		RenderMode m_renderMode;

		//outline
		float m_outLineThickness;
		CU::Vector4f m_outLineColor;
	}; 
}

