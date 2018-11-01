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
		void Update(float deltaTime);
		void AddModel(ModelInstance* instance, bool instanced = false, bool transparent = false);
		void AddLight(Light* light);
		void AddLightShader(std::string id);
		void SetSkyBox(SkyBox* skyBox) { m_skyBox = skyBox; }
		void RenderNormals(bool renderNormals) { m_renderNormals = renderNormals; }
		void RenderWithPostProcess();
		PostProcess& GetPostProcess();
		void SetActive();
	private:
		void SetUniforms();
		void RenderTransparantModels();
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
		bool m_renderNormals = false;
	};
}

