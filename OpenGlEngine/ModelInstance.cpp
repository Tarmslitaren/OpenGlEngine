#include "ModelInstance.h"
#include "Engine.h"
#include "Camera.h"
#include "Light.h"
using namespace GLEN;

GLEN::ModelInstance::ModelInstance(std::string primitiveId, std::string shaderProgram)
{
	m_orientation.SetIdentity();
	m_shaderId = shaderProgram;
	m_model = Engine::GetInstance()->GetModelContainer().GetModel(primitiveId);


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

		light->ApplytoShader(m_shaderId);

		m_model->Render(view, projection);
	}
	//else: do we need to hide somehow?
}
