#include "Light.h"
#include "Engine.h"
using namespace GLEN;

Light::Light(LightType lightType, ModelInstance* instance)
{
	m_type = lightType;
	m_debugRenderObject = instance;
	m_ambient = { 0.1f, 0.1f, 0.1f }; //ambient should be low
	m_diffuse = { 0.5f, 0.5f, 0.5f }; // darken the light a bit to fit the scene
	m_specular = { 1.0f, 1.0f, 1.0f }; //typically specular is 1
}


Light::~Light()
{
}

void GLEN::Light::RenderObject()
{
	if (m_debugRenderObject != nullptr)
	{
		m_debugRenderObject->SetPosition(m_position);
		Light light;
		m_debugRenderObject->Render(&light);
	}
}

void GLEN::Light::ApplytoShader(std::string shaderId)
{

	ShaderProgram& shader = *Engine::GetInstance()->GetShaderContainer().GetShaderProgram(shaderId);
	shader.setVector("light.ambient", m_ambient);
	shader.setVector("light.diffuse", m_diffuse); // darken the light a bit to fit the scene
	shader.setVector("light.specular", m_specular);
	shader.setVector("light.position", m_position);

	//not for point lights
	shader.setVector("light.direction", m_direction);

	//not for dir lights
	shader.setFloat("light.constant", 1.0f);
	shader.setFloat("light.linear", 0.09f);
	shader.setFloat("light.quadratic", 0.032f);

	shader.setFloat("light.cutOff", m_spotlightRadius);
}

void Light::SetAttenuation(float linear, float quadratic, float constant)
{
	m_linear = linear;
	m_quadratic = quadratic;
	m_constant = constant;
}