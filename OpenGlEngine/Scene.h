#pragma once
#include <vector>
#include <map>
#include "Model.h"
#include "Light.h"
#include "ModelInstance.h"
#include "SkyBox.h"
#include "PostProcess.h"
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
		void AddLight(Light* light);
		void AddLightShader(std::string id) { m_lightShaders.push_back(id); }
		void SetSkyBox(SkyBox* skyBox) { m_skyBox = skyBox; }
		void RenderWithPostProcess();
		PostProcess& GetPostProcess();
	private:
		void RenderTransparantModels();
		std::vector<ModelInstance*> m_models;
		std::vector<ModelInstance*> m_transparantModels;
		std::vector<Light*> m_lights;
		std::map<float, ModelInstance*> m_sortingMap; //todo: more efficient sorting
		SkyBox* m_skyBox = nullptr;
		int m_nrOfPointLights = 0;
		std::vector<std::string> m_lightShaders;
		PostProcess m_postProcess;
	};
}

