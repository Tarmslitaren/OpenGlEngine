#include "Scene.h"


using namespace GLEN;
Scene::Scene()
{
}


Scene::~Scene()
{
}

void GLEN::Scene::Render()
{
	for (Primitive* primitive : m_primitives)
	{
		primitive->Render();
	}
}

void GLEN::Scene::Update(float deltaTime)
{
}
