#include "Scene.h"
#include "CU_Matrix.h"


using namespace GLEN;
Scene::Scene()
{
}


Scene::~Scene()
{
}

void GLEN::Scene::Render(CU::Matrix44f view, CU::Matrix44f projection)
{
	for (Primitive* primitive : m_primitives)
	{
		primitive->Render(view, projection);
	}
}

void GLEN::Scene::Update(float deltaTime)
{
}
