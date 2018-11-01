#include "Scene.h"
#include "CU_Matrix.h"
#include <map>
#include "Engine.h"
#include "PostProcess.h"
using namespace GLEN;
Scene::Scene()
{
	AddLightShader("lightShader");
	AddLightShader("explode");
	AddLightShader("lightShaderInstanced");
	
	SetUniforms();
}


Scene::~Scene()
{
}

void GLEN::Scene::Render()
{

	//todo: oct tree culling my god.

	for (Light* light : m_lights)
	{
		light->RenderObject();//for debug use only
		for (std::string id : m_lightShaders)
		{
			light->ApplytoShader(id);
		}
	}

	for (ModelInstance* model : m_models)
	{
		model->Render();
	}
	for (auto it = m_instancedModels.rbegin(); it != m_instancedModels.rend(); ++it)
	{
		std::vector<CU::Matrix44f> models;
		for (int i = 0; i < it->second.size(); i++)
		{
			CU::Matrix44f modelMatrix;
			it->second.at(i)->GetModelMatrix(modelMatrix);
			models.push_back(modelMatrix);
		}
		Model* model = Engine::GetInstance()->GetModelContainer().GetModel(it->first);
		model->RenderInstanced(models);
	}

	for (auto it = m_staticInstancedModels.rbegin(); it != m_staticInstancedModels.rend(); ++it)
	{
		Model* model = Engine::GetInstance()->GetModelContainer().GetModel(it->first);
		if (m_staticInstancedModels[it->first].dirty)
		{
			model->SetStaticModels(m_staticInstancedModels[it->first].modelMatrices);
			m_staticInstancedModels[it->first].dirty = false;
		}
		//todo: no need to save the matrices here. huge waste of memory (64 bytes * nr models)
		model->RenderInstanced(m_staticInstancedModels[it->first].modelMatrices, true);
	}

	//if renderNormals
	if (m_renderNormals) {
		for (ModelInstance* model : m_models)
		{
			model->RenderNormals();
		}
	}

	if (m_skyBox != nullptr)
	{
		m_skyBox->Render();
	}

	RenderTransparantModels();
}

void GLEN::Scene::Update(float deltaTime)
{
}

void GLEN::Scene::AddModel(ModelInstance * instance, bool instanced, bool transparent)
{
	if (transparent == true) {
		m_transparantModels.push_back(instance);
	}
	else
	{
		if (instanced)
		{
			if (instance->GetIsStaic() == true)
			{
				CU::Matrix44f modelMatrix;
				instance->GetModelMatrix(modelMatrix);
				m_staticInstancedModels[instance->GetModelId()].modelInstances.push_back(instance);
				m_staticInstancedModels[instance->GetModelId()].modelMatrices.push_back(modelMatrix);
				
			}
			else
			{
				m_instancedModels[instance->GetModelId()].push_back(instance);
			}
		}
		else
		{
			m_models.push_back(instance);
		}
	}
}

void GLEN::Scene::AddLight(Light * light)
{
	m_lights.push_back(light);
	if (light->GetType() == POINT_LIGHT)
	{
		m_nrOfPointLights++;
		SetUniforms();
	}
}

void GLEN::Scene::AddLightShader(std::string id)
{
	for (auto shader : m_lightShaders)
	{
		if (shader == id)
		{
			//no duplicates
			return;
		}
	}
	m_lightShaders.push_back(id);
}

void GLEN::Scene::RenderWithPostProcess()
{
	m_postProcess.Render(this);
}

PostProcess & GLEN::Scene::GetPostProcess()
{
	return m_postProcess;
}

void GLEN::Scene::SetActive()
{
	SetUniforms();
	
}

void GLEN::Scene::SetUniforms()
{
	for (std::string id : m_lightShaders)
	{
		Engine::GetInstance()->GetShaderContainer().GetShaderProgram(id)->setInt("nrPointLights", m_nrOfPointLights);
	}
}

void GLEN::Scene::RenderTransparantModels()
{
	//naiive sort of transparent items
	m_sortingMap.clear();
	auto cameraPosition = Engine::GetInstance()->GetCamera().GetPosition();
	//naiive sort of transparent items
	for (unsigned int i = 0; i < m_transparantModels.size(); i++)
	{
		CU::Vector3f position = m_transparantModels[i]->GetPosition();
		float distance = (cameraPosition - position).Length2();
		m_sortingMap[distance] = m_transparantModels[i];
	}
	//enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto it = m_sortingMap.rbegin(); it != m_sortingMap.rend(); ++it)
	{
		it->second->Render();
	}
	glDisable(GL_BLEND);

	/*
	Sorting objects with alpha:

	the most common approach:

	-Set DepthBufferEnable and DepthBufferWriteEnable to true
	-Draw all opaque geometry
	-Leave DepthBufferEnable set to true, but change DepthBufferWriteEnable to false
	-Sort alpha blended objects by distance from the camera, then draw them in order from back to front
	This relies on a combination of all three sorting techniques:

	-Opaque objects are sorted by the depth buffer
	-Alpha versus opaque objects are also handled by the depth buffer (so you will never see an alpha blended object through a closer opaque one)
	-Painter’s algorithm sorts alpha blended objects relative to each other (which causes sorting errors if two alpha blended objects intersect)
	-Relies on backface culling to sort the individual triangles within a single alpha blended object (which causes sorting errors if alpha blended objects are not convex)
	The results are not perfect, but this is efficient, reasonably easy to implement, and good enough for most games.

	or this: https://blog.icare3d.org/2010/06/fast-and-accurate-single-pass-buffer.html
*/
}
