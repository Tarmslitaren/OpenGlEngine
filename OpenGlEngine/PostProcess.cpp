#include "PostProcess.h"
#include "glad/glad.h"
#include <iostream>
#include "Engine.h"
#include "Material.h"
#include "ErrorHandler.h"
using namespace GLEN;

PostProcess::PostProcess()
{

	SetupInfo info = Engine::GetInstance()->GetSetupInfo();
	//init frame buffer
	glGenFramebuffers(1, &m_frameBufferObject);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObject);


	//init texture
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.m_resolution.width, info.m_resolution.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	//attach texture to frame buffer as color
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);


	//init renderbuffer with depth+stencil
	glGenRenderbuffers(1, &m_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, info.m_resolution.width, info.m_resolution.height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferObject);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//to attach texture to frame buffer as depth +stencil:
	/*glTexImage2D(
		GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0,
		GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
	);*/

	//create shader
	//todo: create all kinds of shaders and put in container
	m_shader = Engine::GetInstance()->GetShaderContainer().CreateShaderProgram("pp_simple", "pp_simple.vert", "pp_simple.frag");
	Engine::GetInstance()->GetShaderContainer().CreateShaderProgram("pp_grayscale", "pp_simple.vert", "pp_grayscale.frag");
	Engine::GetInstance()->GetShaderContainer().CreateShaderProgram("pp_invert", "pp_simple.vert", "pp_invert.frag");
	Engine::GetInstance()->GetShaderContainer().CreateShaderProgram("pp_blur", "pp_simple.vert", "pp_blur.frag");
	Engine::GetInstance()->GetShaderContainer().CreateShaderProgram("pp_sharpen", "pp_simple.vert", "pp_sharpen.frag");
	Engine::GetInstance()->GetShaderContainer().CreateShaderProgram("pp_edges", "pp_simple.vert", "pp_edges.frag");
	


	Material material("pp_simple");
	material.AddDiffuseTexture(m_texture, 0);
	int meshId = Engine::GetInstance()->GetMeshContainer().CreateQuad("pp_quad", { 2,2,0 },material);
	m_quad = Engine::GetInstance()->GetMeshContainer().GetMesh(meshId);

	//m_quad.SetPolygonMode(POLYGONMODE_LINE); //show the quad

}


PostProcess::~PostProcess()
{
	glDeleteFramebuffers(1, &m_frameBufferObject);
}

void GLEN::PostProcess::Render(Scene* scene)
{
		/*to draw the scene to a single texture we'll have to take the following steps:

		-Render the scene as usual with the new framebuffer bound as the active framebuffer.
		-Bind to the default framebuffer.
		-Draw a quad that spans the entire screen with the new framebuffer's color buffer as its texture.
		*/
		// first pass
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObject);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
	glEnable(GL_DEPTH_TEST);

	scene->Render();

	// second pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//draw quad
	m_shader->use();
	glDisable(GL_DEPTH_TEST);
	m_quad->Render(CU::Matrix44f::Identity());

	
}

void GLEN::PostProcess::SetShader(std::string id)
{
	m_shader = Engine::GetInstance()->GetShaderContainer().GetShaderProgram(id);
	m_quad->GetMaterial().SetShader(m_shader);
}
