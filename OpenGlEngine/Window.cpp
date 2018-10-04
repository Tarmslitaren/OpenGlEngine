#include "Window.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

using namespace GLEN;
Window::Window(SetupInfo setupInfo)
{
	Create(setupInfo);
}


Window::~Window()
{
}


bool Window::Update()
{
	if (glfwWindowShouldClose(m_window))
	{
		return false;
	}
	
	glfwSwapBuffers(m_window);
	glfwPollEvents();
	return true;
}

void Window::Destroy()
{
	glfwTerminate();
}

void GLEN::Window::RequestCloseWindow()
{
	glfwSetWindowShouldClose(m_window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

	//todo: what if we dont want to allow user resize of window?
	glViewport(0, 0, width, height);
}

void Window::Create(SetupInfo setupInfo)
{

	//glfw init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //this needed for mac osX

	m_window = glfwCreateWindow(setupInfo.m_resolution.width, setupInfo.m_resolution.height, "LearnOpenGL", NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_window);

	//glad init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, setupInfo.m_resolution.width, setupInfo.m_resolution.height);

	//register callback for window rezise event
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

}
