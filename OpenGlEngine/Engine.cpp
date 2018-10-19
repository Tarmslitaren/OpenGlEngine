#include "Engine.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "stb_image.h"

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

	//enable z-ordering
	glEnable(GL_DEPTH_TEST);

	//enable stencil 
	glEnable(GL_STENCIL_TEST);

	//test
	//glDepthFunc(GL_ALWAYS);



	//this can potentially increase performace > 50% but onl yworks for models with properly winded triangles...
	//glEnable(GL_CULL_FACE);

	stbi_set_flip_vertically_on_load(true); //flips the coords, because opengl wants it so.


	GetShaderContainer().CreateShaderProgram("singleColorScale", "scale.vert", "singleColor.frag");
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
		std::cout << "GLEN: Tried to create more than one engine." << std::endl;
	}
	return s_instance;
}

void GLEN::Engine::RenderScene()
{
	//clear color for test
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glStencilMask(0x00); //reset stencil
}

void Engine::Destroy()
{
	m_window.Destroy();
}

bool GLEN::Engine::Update(float deltaTime)
{
	m_input.Update(deltaTime);
	return m_window.Update();
}
