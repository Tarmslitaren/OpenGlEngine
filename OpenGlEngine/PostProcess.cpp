#include "PostProcess.h"
#include "glad/glad.h"
#include <iostream>
#include "Engine.h"
#include "Material.h"
#include "ErrorHandler.h"
using namespace GLEN;


unsigned int quadVAO, quadVBO;
PostProcess::PostProcess()
	:m_quad(Material("pp_simple"))
{

	//init frame buffer
	glGenFramebuffers(1, &m_frameBufferObject);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObject);


	//init texture
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); //todo: no hard coded screen size
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	//attach texture to frame buffer as color
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);


	//init renderbuffer with depth+stencil
	glGenRenderbuffers(1, &m_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
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


	//create a quad
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
	};

	//possible issue: mesh init does not handle 2d positions.

	VertexLayout layout;
	layout.hasNormals = false;
	layout.stride = 4;
	layout.hasTexCoords = true;
	layout.texCoordOffset = 2;
	layout.texCoordAttribute = 1;

	m_quad.SetVerticeData(quadVertices, 24, layout);
	m_quad.Finalize(GLEN::STATIC_DRAW, "pp_quad");
	
	//Material material(m_shader->GetId());
	m_quad.GetMaterial().AddDiffuseTexture(m_texture, 0);
	m_quad.SetPolygonMode(POLYGONMODE_LINE); //show the quad

	//m_quad.ChangeMaterial(material);


	// screen quad VAO
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	//m_shader->setInt("screenTexture", 0);
	ErrorHandler::CheckError();

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
	ErrorHandler::CheckErrorOnce("PostProcess 0");
		// first pass
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObject);
	ErrorHandler::CheckErrorOnce("PostProcess 1");
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
	glEnable(GL_DEPTH_TEST);

	scene->Render();
	ErrorHandler::CheckErrorOnce("PostProcess 2");

	// second pass
	/*glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//draw quad
	m_shader->use();
	glDisable(GL_DEPTH_TEST);
	m_quad.Render(CU::Matrix44f::Identity());*/
	
	//glPolygonMode(GL_FRONT_AND_BACK, POLYGONMODE_LINE);

	// second pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_shader->use();
	glBindVertexArray(quadVAO);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	ErrorHandler::CheckErrorOnce("PostProcess 3");
	
}

void GLEN::PostProcess::SetShader(std::string id)
{
	m_shader = Engine::GetInstance()->GetShaderContainer().GetShaderProgram(id);
}
