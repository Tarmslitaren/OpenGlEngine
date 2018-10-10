#include "Input.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "engine.h"
using namespace GLEN;

//todo: own enum for all GLFW key defines

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	for (auto listener : GLEN::Engine::GetInstance()->GetInput().GetListeners())
	{
		listener->PointerEvent(CU::Vector2f(static_cast<float>(xpos), static_cast<float>(ypos)));
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

	for (auto listener : GLEN::Engine::GetInstance()->GetInput().GetListeners())
	{
		listener->ScrollEvent(CU::Vector2f(static_cast<float>(xoffset), static_cast<float>(yoffset)));
	}
}


Input::Input(GLFWwindow& window)
:m_window(window)
{

	glfwSetCursorPosCallback(&m_window, mouse_callback);
	glfwSetScrollCallback(&m_window, scroll_callback);
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

void GLEN::Input::CaptureMouseAndDisablePointer()
{
	glfwSetInputMode(&m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void GLEN::Input::Update(float deltaTime)
{
}


