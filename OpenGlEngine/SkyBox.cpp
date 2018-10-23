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
	VertexLayout layout;
	layout.stride = 3;
	layout.hasNormals = false;
	layout.hasTexCoords = false;
	int meshId = Engine::GetInstance()->GetMeshContainer().CreateMesh("skybox", m_skyboxVertices, sizeof(m_skyboxVertices) / sizeof(float), layout, material);
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
	auto projection = cam.GetProjection();
	auto view = cam.GetView();
	view.SetPosition({ 0,0,0 });
	CU::Matrix44f model;
	m_mesh->Render(model);
	m_shader->setMatrix("view", view);
	m_shader->setMatrix("projection", projection);

	glDepthFunc(GL_LESS); // set depth function back to default

}