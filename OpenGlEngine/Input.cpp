#include "Input.h"
#include <GLFW/glfw3.h>

using namespace GLEN;

//todo: own enum for all GLFW key defines

Input::Input(GLFWwindow& window)
:m_window(window)
{
}


Input::~Input()
{
}

bool GLEN::Input::GetKeyPressed(int keyId)
{
	if (glfwGetKey(&m_window, keyId) == GLFW_PRESS)
	{
		return true;
	}
	return false;
}

