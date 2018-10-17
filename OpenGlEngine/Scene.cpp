#include "Scene.h"
#include "CU_Matrix.h"


using namespace GLEN;
Scene::Scene()
{
}


Scene::~Scene()
{
}

void GLEN::Scene::Render()
{
	for (Light* light : m_lights)
	{
		light->RenderObject();//for debug use only

		for (ModelInstance* model : m_models)
		{
			model->Render(light);
		}
	}
}

void GLEN::Scene::Update(float deltaTime)
{
}
