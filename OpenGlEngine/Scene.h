#pragma once
#include <vector>
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
		void AddModel(ModelInstance* instance) { m_models.push_back(instance); }
		void AddLight(Light* light) { m_lights.push_back(light); }
	private:
		std::vector<ModelInstance*> m_models;
		std::vector<Light*> m_lights;
	};
}

