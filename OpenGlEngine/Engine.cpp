#include "Engine.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "ErrorHandler.h"
using namespace GLEN;
Engine* Engine::s_instance = nullptr;

Engine::Engine(const SetupInfo& infoArgument)
:m_window(infoArgument), 
m_input(m_window.GetWindow())
{
	m_SetupInfo = infoArgument;
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

	glEnable(GL_MULTISAMPLE); //this is most likely enabled by default. wont work on post process, so had to code that seperately in postprocess.

	//glEnable(GL_FRAMEBUFFER_SRGB); //enable gama correction. only use if not using post process effects.

	//this can potentially increase performace > 50% but onl yworks for models with properly winded triangles...
	//glEnable(GL_CULL_FACE);

	stbi_set_flip_vertically_on_load(true); //flips the coords, because opengl wants it so.


	m_shaderContainer.CreateShaderProgram("singleColorScale", "scale.vert", "singleColor.frag");

	//is this the place? or is it in shader container? or light container?
	m_shaderContainer.CreateShaderProgram("lightShader", "lightingShader.vert", "lightingShader.frag");
	m_shaderContainer.CreateShaderProgram("reflectShader", "reflection.vert", "reflection.frag");
	m_shaderContainer.CreateShaderProgram("refractShader", "reflection.vert", "refraction.frag");
	//Engine::GetInstance()->GetShaderContainer().CreateShaderProgram("depthTestShader", "depthTest.vert", "depthTest.frag");


	m_shaderContainer.CreateShaderProgram("lampShader", "lampShader.vert", "lampShader.frag");

	m_shaderContainer.CreateShaderProgram("drawNormals", "drawNormals.vert", "singleColor.frag", "drawNormals.geom");

	m_shaderContainer.CreateShaderProgram("explode", "lightingShader.vert", "lightingShaderGeom.frag", "explode.geom");

	m_shaderContainer.CreateShaderProgram("lightShaderInstanced", "lightingShaderInstanced.vert", "lightingShader.frag");

	m_shaderContainer.CreateShaderProgram("noLightShaderInstanced", "lightingShaderInstanced.vert", "textureNoLighting.frag");
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glStencilMask(0x00); //reset stencil
	m_sceneContainer.GetCurrentScene().RenderWithPostProcess();
}

void Engine::Destroy()
{
	m_window.Destroy();
}

bool GLEN::Engine::Update(float deltaTime)
{
	m_input.Update(deltaTime);

	m_shaderInput.UpdateStandardUniforms();
	return m_window.Update();
}
