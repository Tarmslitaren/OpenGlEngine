#pragma once
#include "Window.h"
#include <vector>
#include "Input.h"
#include "enums.h"
#include "Camera.h"
#include "TextureContainer.h"
#include "ShaderContainer.h"
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
		//ModelContainer& GetModelContainer() { return myModelContainer; }


	private:
		//bool D3DViewPortSetup();
		//bool ZBufferSetup();
		Engine();
		virtual ~Engine();
		Engine(const SetupInfo & infoArgument);
		static Engine* s_instance;
		Window m_window;
		Input m_input;
		Camera m_camera; //todo: allow for several cameras
		TextureContainer m_textureContainer;
		ShaderContainer m_shaderContainer;


	};
};

