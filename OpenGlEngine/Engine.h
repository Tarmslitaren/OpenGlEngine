#pragma once
#include "Window.h"
#include <vector>
#include "Input.h"
#include "Camera.h"
#include "TextureContainer.h"
#include "ShaderContainer.h"
#include "ModelContainer.h"
#include "MeshContainer.h"
#include "Scene.h"
#include "ShaderInput.h"
namespace GLEN
{

	class Engine
	{
	public:
		static Engine* GetInstance() { return(s_instance); }

		static Engine* Create(const SetupInfo& infoArgument);

		void RenderScene();
		void Destroy();
		bool Update(float deltatime);
		Input& GetInput() { return m_input; }
		Camera& GetCamera() { return m_camera; }
		TextureContainer& GetTextureContainer() { return m_textureContainer; }
		ShaderContainer& GetShaderContainer() { return m_shaderContainer; }
		//EffectInput& GetEffectInput() { return myEffectInput; }
		ModelContainer& GetModelContainer() { return m_modelContainer; }
		MeshContainer& GetMeshContainer() { return m_meshContainer; }
		Scene& GetCurrentScene() { return *m_scenes[m_currentScene]; }
		SetupInfo& GetSetupInfo() { return m_SetupInfo; }
		ShaderInput& GetShaderInput() { return m_shaderInput; }


	private:
		void InitScene();
		Engine();
		virtual ~Engine();
		Engine(const SetupInfo & infoArgument);
		static Engine* s_instance;
		Window m_window;
		Input m_input;
		Camera m_camera; //todo: allow for several cameras (let scene own camwera)
		TextureContainer m_textureContainer;
		ShaderContainer m_shaderContainer;
		ModelContainer m_modelContainer;
		MeshContainer m_meshContainer;
		std::vector < Scene* > m_scenes; //todo: scene container/handler with loading/unloading and switching scenes
		int m_currentScene = 0;
		SetupInfo m_SetupInfo;
		ShaderInput m_shaderInput;

	};
};

