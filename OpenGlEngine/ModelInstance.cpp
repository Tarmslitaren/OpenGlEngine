#include "ModelInstance.h"
#include "Engine.h"
#include "Camera.h"
#include "Light.h"
using namespace GLEN;

GLEN::ModelInstance::ModelInstance(std::string modelId, std::string shaderProgram)
{
	m_orientation.SetIdentity();
	m_shaderId = shaderProgram;
	m_model = Engine::GetInstance()->GetModelContainer().GetModel(modelId);


}

ModelInstance::~ModelInstance()
{
}

void GLEN::ModelInstance::Render(Light* light)
{

	if (m_isToRender)
	{
		Camera cam = Engine::GetInstance()->GetCamera();
		auto projection = cam.GetProjection();
		auto view = cam.GetView();


		//todo: issue: we are setting these vaiables without knowing if they exist in the current shader. 
		//soultion: material owns the shader. all uniforms sets to the material
		ShaderProgram& shader = *Engine::GetInstance()->GetShaderContainer().GetShaderProgram(m_shaderId);
		//m_shaderProgram.setMatrix("transform", m_model * view * projection);
		CU::Matrix44f matrix = CU::Matrix44f::Identity();
		matrix = m_orientation;
		matrix.SetPosition(m_position);
		shader.setMatrix("model", matrix);
		shader.setMatrix("view", view);
		shader.setMatrix("projection", projection);

		shader.setVector("viewPos", cam.GetPosition());
		if (light)
		{
			light->ApplytoShader(m_shaderId);
		}

		if (m_outLineThickness > 0)
		{
			DrawOutline(); //for
		}
		else {
			m_model->Render();
		}
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
	Camera cam = Engine::GetInstance()->GetCamera();
	auto projection = cam.GetProjection();
	auto view = cam.GetView();


	glEnable(GL_DEPTH_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //use the stencil

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments should update the stencil buffer
	glStencilMask(0xFF); // enable writing to the stencil buffer
	m_model->Render();


	
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);



	//todo: issue: we are setting these vaiables without knowing if they exist in the current shader. 
	//soultion: material owns the shader. all uniforms sets to the material
	ShaderProgram& shader = *Engine::GetInstance()->GetShaderContainer().GetShaderProgram("singleColorScale");
	//m_shaderProgram.setMatrix("transform", m_model * view * projection);
	CU::Matrix44f matrix = CU::Matrix44f::Identity();
	matrix = m_orientation;
	matrix.SetPosition(m_position);
	shader.setMatrix("model", matrix);
	shader.setMatrix("view", view);
	shader.setMatrix("projection", projection);

	shader.setFloat("scaleUp", m_outLineThickness);
	shader.setVector4("color", m_outLineColor);
	//todo: support changing color
	m_model->Render();

	//reset
	glStencilMask(0xFF);
	glEnable(GL_DEPTH_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //reset stencil
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	Engine::GetInstance()->GetShaderContainer().GetShaderProgram(m_shaderId)->use();
	
}