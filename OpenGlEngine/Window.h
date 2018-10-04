#pragma once
#include "enums.h"
struct GLFWwindow;
namespace GLEN {
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

