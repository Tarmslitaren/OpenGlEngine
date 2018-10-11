#include "ModelInstance.h"
#include "Engine.h"
#include "Camera.h"
#include "Light.h"
using namespace GLEN;

GLEN::ModelInstance::ModelInstance(std::string primitiveId, std::string shaderProgram)
{
	m_orientation.SetIdentity();
	m_shaderId = shaderProgram;
	m_primitive = Engine::GetInstance()->GetModelContainer().GetPrimitive(primitiveId);

	ShaderProgram& shader = *Engine::GetInstance()->GetShaderContainer().GetShaderProgram(m_shaderId);
	shader.use();
	//shader.setVector("viewPos", engine.GetCamera().GetPosition());

	//material: is this really the place? or does the primitive own the material and texture
	shader.setVector("material.ambient", { 1.0f, 0.5f, 0.31f });
	shader.setVector("material.diffuse", { 1.0f, 0.5f, 0.31f });
	shader.setVector("material.specular", { 0.5f, 0.5f, 0.5f });
	shader.setFloat("material.shininess", 32.0f);

}

ModelInstance::~ModelInstance()
{
}

void GLEN::ModelInstance::Render(Light* light)
{

	if (m_isToRender)
	{
		Camera cam = Engine::GetInstance()->GetCamera();
		auto projection = cam.getProjection();
		auto view = cam.getView();

		ShaderProgram& shader = *Engine::GetInstance()->GetShaderContainer().GetShaderProgram(m_shaderId);
		shader.use();
		//m_shaderProgram.setMatrix("transform", m_model * view * projection);
		CU::Matrix44f matrix = CU::Matrix44f::Identity();
		matrix = m_orientation;
		matrix.SetPosition(m_position);
		shader.setMatrix("model", matrix);
		shader.setMatrix("view", view);
		shader.setMatrix("projection", projection);

		shader.setVector("viewPos", cam.GetPosition());

		//light
		shader.setVector("light.ambient", light->GetAmbient());
		shader.setVector("light.diffuse", light->GetDiffuse()); // darken the light a bit to fit the scene
		shader.setVector("light.specular", light->GetSpecular());

		shader.setVector("lightPos", light->GetPosition());


		m_primitive->Render(view, projection);
	}
	//else: do we need to hide somehow?
}
