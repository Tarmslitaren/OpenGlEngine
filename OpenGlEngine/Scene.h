#pragma once
#include <vector>
#include <map>
#include "Model.h"
#include "Light.h"
#include "ModelInstance.h"
namespace GLEN
{
	class Scene
	{
	public:
		Scene();
		~Scene();
		void Render();
		void Update(float deltaTime);
		void AddModel(ModelInstance* instance, bool transparent = false);
		void AddLight(Light* light) { m_lights.push_back(light); }
	private:
		std::vector<ModelInstance*> m_models;
		std::vector<ModelInstance*> m_transparantModels;
		std::vector<Light*> m_lights;
		std::map<float, ModelInstance*> m_sortingMap;
	};
}

