#include "Light.h"
#include "Engine.h"
#include "Converters.h"
using namespace GLEN;

Light::Light(LightType lightType, ModelInstance* instance, int index)
{
	m_index = index;
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
		m_debugRenderObject->Render();
	}
}

void GLEN::Light::ApplytoShader(std::string shaderId)
{
	//todo: question is if the shader bindings should be more generic and set/bound by external object
	//nope: the material will decide on shader and bindings
	ShaderProgram& shader = *Engine::GetInstance()->GetShaderContainer().GetShaderProgram(shaderId);
	std::string prefix;
	if (m_type == DIRECTIONAL_LIGHT)
	{
		prefix = "dirLight.";
		shader.setVector("dirLight.direction", m_direction);
	}
	else if (m_type == POINT_LIGHT)
	{
		prefix = "pointLights[" + Convert::IntToString(m_index) + "].";

	}
	else if (m_type == SPOT_LIGHT)
	{ 
		prefix = "spotLight.";
		shader.setFloat("spotLight.cutOff", m_spotlightRadius);
		shader.setFloat("spotLight.outerCutOff", m_spotlightRadiusOuter);
		shader.setVector("spotLight.direction", m_direction);
	}
	
	shader.setVector(prefix + "ambient", m_ambient);
	shader.setVector(prefix + "diffuse", m_diffuse);
	shader.setVector(prefix + "specular", m_specular);
	shader.setVector(prefix + "position", m_position);
	if (m_type != DIRECTIONAL_LIGHT)
	{
		shader.setFloat(prefix + "constant", m_constant);
		shader.setFloat(prefix + "linear", m_linear);
		shader.setFloat(prefix + "quadratic", m_quadratic);
	}
}

void Light::SetAttenuation(float linear, float quadratic, float constant)
{
	m_linear = linear;
	m_quadratic = quadratic;
	m_constant = constant;
}

void GLEN::Light::SetSpotlightRadius(float radius, float outerRadius)
{
	m_spotlightRadius = cos(Convert::DegreeToRadian(radius));
	m_spotlightRadiusOuter = cos(Convert::DegreeToRadian(outerRadius));
}
