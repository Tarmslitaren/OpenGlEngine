#include "ShadowMap.h"
#include "glad/glad.h"
#include "Scene.h"
#include "Engine.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "ErrorHandler.h"
#include "Light.h"
#include "VectorMath.h"

using namespace GLEN;

ShadowMap::ShadowMap()
{


	m_shader = Engine::GetInstance()->GetShaderContainer().CreateShaderProgram("shadow", "shadow.vert", "shadow.frag");

	glGenFramebuffers(1, &m_depthMapFrameBufferObject);

	glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFrameBufferObject);

	//Create a 2D texture that we'll use as the framebuffer's depth buffer :
	glGenTextures(1, &m_depthMapTexture);
	glBindTexture(GL_TEXTURE_2D, m_depthMapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_depthTextureResolution, m_depthTextureResolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//attach it as the framebuffer's depth buffer:
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMapTexture, 0);

	/*
	We only need the depth information when rendering the scene from the light's perspective so there is no need for a color buffer.
	A framebuffer object however is not complete without a color buffer so we need to explicitly tell OpenGL we're not going to render any color data. 
	We do this by setting both the read and draw buffer to GL_NONE with glDrawBuffer and glReadbuffer.
	*/
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//setup light projection matrix
	float nearPlane = 1.0f, farPlane = 7.5f;
	m_LightPerspective.SetProjection(45, Engine::GetInstance()->GetSetupInfo().m_resolution.width / Engine::GetInstance()->GetSetupInfo().m_resolution.height, 0.1, 1000);
	m_lightProjection = m_LightPerspective.GetProjection(); //glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	//todo: need orthographic projection for this...? yeah but onl y for directional light though...


	//init debuggin
	m_debugShader = Engine::GetInstance()->GetShaderContainer().GetShaderProgram("depthTest");
	m_debugShader->setFloat("nearPlane", 0.1);
	m_debugShader->setFloat("farPlane", 100);

	Material material("depthTest");
	material.AddDiffuseTexture(m_depthMapTexture, 0);

	int meshId = Engine::GetInstance()->GetMeshContainer().CreateQuad("shadow_quad", { 1,1,0 }, material);
	m_debugQuad = Engine::GetInstance()->GetMeshContainer().GetMesh(meshId);
	//m_debugQuad->SetPolygonMode(POLYGONMODE_LINE); //show the quad

		// shader configuration
	// --------------------
	Engine::GetInstance()->GetShaderContainer().GetShaderProgram("lightShaderShadows")->setInt("shadowMap", m_shadowMapBinding); //shadowmap handle instead of 1???

	m_debugShader->setInt("depthMap", 0);
}


ShadowMap::~ShadowMap()
{
}

void GLEN::ShadowMap::Render(Scene * scene)
{
	//fetch light pos:
	Light* light = scene->GetLight(0);
	m_LightPerspective.SetPosition(light->GetPosition());
	m_LightPerspective.SetOrientation(light->GetDirection());
	CU::Matrix44f lightView = m_LightPerspective.GetView();

	//lightView = Engine::GetInstance()->GetCamera().GetView();
	//m_lightProjection = Engine::GetInstance()->GetCamera().GetProjection();


	CU::Matrix44f lightSpaceMatrix = lightView * m_lightProjection;
	m_shader->setMatrix("lightSpaceMatrix", lightSpaceMatrix);
	Engine::GetInstance()->GetShaderContainer().GetShaderProgram("depthTest")->setMatrix("lightSpaceMatrix", lightSpaceMatrix);
	Engine::GetInstance()->GetShaderContainer().GetShaderProgram("lightShaderShadows")->setMatrix("lightSpaceMatrix", lightSpaceMatrix);


	glViewport(0, 0, m_depthTextureResolution, m_depthTextureResolution);
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFrameBufferObject);
	glClear(GL_DEPTH_BUFFER_BIT);

	//render from lights point of view
	scene->RenderShadows(); //render with post process?
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// 2. then render scene as normal with shadow mapping (using depth map)
	glViewport(0, 0, Engine::GetInstance()->GetSetupInfo().m_resolution.width, Engine::GetInstance()->GetSetupInfo().m_resolution.height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glActiveTexture(GL_TEXTURE0 + m_shadowMapBinding); // activate proper texture unit before binding
	glBindTexture(GL_TEXTURE_2D, m_depthMapTexture); //should not be needed

	scene->Render();//render with post process?


	if (m_debugMode == true)
	{
		// render Depth map to quad for visual debugging
		CU::Matrix44f model = CU::Matrix44f::Identity();
		model.SetPosition({ 300, 300, 0 });
		m_debugQuad->Render(model);
	}
}
