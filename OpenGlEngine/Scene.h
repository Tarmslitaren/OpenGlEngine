#pragma once
#include <vector>
#include <map>
#include "Model.h"
#include "Light.h"
#include "ModelInstance.h"
#include "SkyBox.h"
#include "PostProcess.h"
#include "ShadowMap.h"
namespace GLEN
{
	struct StaticInstanceModelData
	{
		std::vector<ModelInstance*> modelInstances;
		std::vector<CU::Matrix44f> modelMatrices;
		bool dirty = true;
	};
	class Scene
	{
	public:
		Scene();
		~Scene();
		void Render();
		void RenderShadows();
		void Update(float deltaTime);
		void AddModel(ModelInstance* instance, bool instanced = false, bool transparent = false);
		void AddLight(Light* light);
		void AddLightShader(std::string id);
		void SetSkyBox(SkyBox* skyBox) { m_skyBox = skyBox; }
		void RenderNormals(bool renderNormals) { m_renderNormals = renderNormals; }
		void RenderWithPostProcess();
		void RenderWithShadows();
		PostProcess& GetPostProcess();
		void SetActive();
		Light* GetLight(int index); //todo: nicer interface. let lights have identifiers nad a container
	private:
		void SetUniforms();
		void RenderTransparantModels();
		void RenderInstancedModels();
		std::vector<ModelInstance*> m_models;
		std::vector<ModelInstance*> m_transparantModels;
		std::vector<Light*> m_lights;
		std::map<std::string, std::vector<ModelInstance*> > m_instancedModels;
		std::map<std::string, StaticInstanceModelData > m_staticInstancedModels;
		std::map<float, ModelInstance*> m_sortingMap; //todo: more efficient sorting
		SkyBox* m_skyBox = nullptr;
		int m_nrOfPointLights = 0;
		std::vector<std::string> m_lightShaders;
		PostProcess m_postProcess;
		ShadowMap m_shadowMap;
		bool m_renderNormals = false;
		bool m_renderShadows = true;
	};
}

