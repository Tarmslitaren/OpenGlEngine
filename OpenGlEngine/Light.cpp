#include "Light.h"

using namespace GLEN;

Light::Light(ModelInstance* instance)
{
	m_debugRenderObject = instance;
	m_ambient = { 0.2f, 0.2f, 0.2f }; //ambient should be low
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