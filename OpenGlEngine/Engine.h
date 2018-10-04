#pragma once
#include "Window.h"
#include "Input.h"
#include "enums.h"
namespace GLEN
{

	class Engine
	{
	public:
		virtual ~Engine();
		static Engine* GetInstance() { return(s_instance); }

		static Engine* Create(const SetupInfo& infoArgument);

		void RenderScene();
		void Destroy();
		bool Update();
		Input& GetInput() { return m_input; }
		//ID3D10Device* GetDevice() { return(my3DDevice); };
		//TextureContainer& GetTextureContainer() { return myTextureContainer; }
		//EffectContainer& GetEffectContainer() { return m_effectContainer; }
		//EffectInput& GetEffectInput() { return myEffectInput; }
		//ModelContainer& GetModelContainer() { return myModelContainer; }


	private:
		//bool Init(HWND& aHwnd, WNDPROC aWindowProc, const SetupInfo& aInfoArgument);
		//bool WindowSetup(WNDPROC aWindowProc, const SetupInfo& aInfoArgument);
		//bool D3DSetup();
		//bool D3DDeviceSetup();
		//bool D3DViewPortSetup();
		//bool ZBufferSetup();

		Engine(const SetupInfo & infoArgument);
		static Engine* s_instance;
		Window m_window;
		Input m_input;
		//EffectContainer m_effectContainer;


	};
};

