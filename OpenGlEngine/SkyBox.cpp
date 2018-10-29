#include "SkyBox.h"
#include "Engine.h"
#include "ErrorHandler.h"
using namespace GLEN;

GLEN::SkyBox::SkyBox(std::string id, std::vector<std::pair<std::string, GLEN::CubeMapOrientation>> cubemapImages)
{
	m_texture = Engine::GetInstance()->GetTextureContainer().LoadCubeMap(id, cubemapImages);
	m_shader = Engine::GetInstance()->GetShaderContainer().CreateShaderProgram("skybox", "skybox.vert", "skybox.frag");
	Material material(m_shader->GetId());
	material.SetCubeMapTexture(m_texture->getPath());
	material.InitShaderVariables();

	int meshId = Engine::GetInstance()->GetMeshContainer().CreateBox("skybox", { 1,1,1 }, material);
	m_mesh = Engine::GetInstance()->GetMeshContainer().GetMesh(meshId);


}

SkyBox::~SkyBox()
{
}

void GLEN::SkyBox::Render()
{
	//should be rendered last for best performance

	glDepthFunc(GL_LEQUAL);
	Camera cam = Engine::GetInstance()->GetCamera();
	auto view = cam.GetView();
	m_mesh->Render();

	view.SetPosition({ 0,0,0 });
	m_shader->setMatrix("staticView", view);

	glDepthFunc(GL_LESS); // set depth function back to default

}