#pragma once
#include "CU_Vector.h"
struct GLFWwindow;
namespace GLEN {

	struct SetupInfo
	{
		//bool myWindowedMode;
		CU::Vector2<int> m_resolution{ 800, 600 };
		//int myColorDepth;
		//int myZBufferDepth;
		//int myStencilDepth;
		//std::string mySessionName;
	};

	class Window
	{
	public:
		Window(SetupInfo setupInfo);
		~Window();
		bool Update();
		void Destroy();
		void RequestCloseWindow();

		GLFWwindow& GetWindow() { return *m_window; }
	 
	private:
		void Create(SetupInfo setupInfo);
		GLFWwindow* m_window;

		
	};
}

