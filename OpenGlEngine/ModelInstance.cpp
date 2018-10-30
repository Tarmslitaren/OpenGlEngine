#include "ModelInstance.h"
#include "Engine.h"
#include "Camera.h"
#include "Light.h"
using namespace GLEN;

GLEN::ModelInstance::ModelInstance(std::string modelId)
{
	m_renderMode = RENDERMODE_TRIANGLES;
	m_orientation.SetIdentity();
	m_model = Engine::GetInstance()->GetModelContainer().GetModel(modelId);


}

ModelInstance::~ModelInstance()
{
}

void GLEN::ModelInstance::Render()
{

	if (m_isToRender)
	{

		CU::Matrix44f matrix = CU::Matrix44f::Identity();
		matrix = m_orientation;
		matrix.SetPosition(m_position);

		if (m_outLineThickness > 0)
		{
			DrawOutline();
		}
		else {
			m_model->Render(matrix, m_renderMode);
		}
	}
	//else: do we need to hide somehow?
}

void GLEN::ModelInstance::RenderNormals()
{
	if (m_isToRender)
	{

		CU::Matrix44f matrix = CU::Matrix44f::Identity();
		matrix = m_orientation;
		matrix.SetPosition(m_position);

		m_model->Render(matrix, "drawNormals", m_renderMode);
		m_model->Render(matrix, m_renderMode);
	}
	//else: do we need to hide somehow?
}

void GLEN::ModelInstance::SetOutline(float thickness, CU::Vector4f color)
{
	m_outLineThickness = thickness;
	m_outLineColor = color;
}


void GLEN::ModelInstance::DrawOutline()
{
	//todo: thsi doesn't work with postprocess on
	Camera cam = Engine::GetInstance()->GetCamera();


	glEnable(GL_DEPTH_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //use the stencil

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments should update the stencil buffer
	glStencilMask(0xFF); // enable writing to the stencil buffer

	CU::Matrix44f matrix = CU::Matrix44f::Identity();
	matrix = m_orientation;
	matrix.SetPosition(m_position);
	m_model->Render(matrix);


	
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);



	ShaderProgram& shader = *Engine::GetInstance()->GetShaderContainer().GetShaderProgram("singleColorScale");

	shader.setMatrix("model", matrix);

	shader.setFloat("scaleUp", m_outLineThickness);
	shader.setVector4("color", m_outLineColor);
	//todo: support changing color
	m_model->Render(matrix);

	//reset
	glStencilMask(0xFF);
	glEnable(GL_DEPTH_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //reset stencil
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//Engine::GetInstance()->GetShaderContainer().GetShaderProgram(m_shaderId)->use();
	
}