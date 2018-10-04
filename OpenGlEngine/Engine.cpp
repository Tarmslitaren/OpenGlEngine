#include "Engine.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

using namespace GLEN;
Engine* Engine::s_instance = nullptr;

Engine::Engine(const SetupInfo& infoArgument)
:m_window(infoArgument), 
m_input(m_window.GetWindow())
{

	//query amount of vetex attributes supported by system (usually 16.)
	//a vertex attribute is the same as it's input variables
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}


Engine::~Engine()
{
}

Engine* Engine::Create(const SetupInfo & infoArgument)
{
	if (s_instance == nullptr)
	{
		s_instance = new Engine(infoArgument);
		
	}
	else
	{
		//log logic error
	}
	return s_instance;
}

void GLEN::Engine::RenderScene()
{
	//clear color for test
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Engine::Destroy()
{
	m_window.Destroy();
}

bool GLEN::Engine::Update()
{
	return m_window.Update();
}
