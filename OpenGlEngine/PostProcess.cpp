#include "PostProcess.h"
#include "glad/glad.h"
#include <iostream>
#include "Engine.h"
#include "Material.h"
using namespace GLEN;

PostProcess::PostProcess()
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
	m_shader = Engine::GetInstance()->GetShaderContainer().CreateShaderProgram("pp", "pp_simple.vert", "pp_simple.frag");


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
	
	Material material;
	material.AddDiffuseTexture(m_texture, 0);
	material.SetShader(m_shader->GetHandle());
	//m_quad.SetPolygonMode(POLYGONMODE_LINE); //show the quad

	m_quad.SetMaterial(material);


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
	//DrawScene();

	// second pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//draw quad
	m_shader->use();
	glDisable(GL_DEPTH_TEST);
	m_quad.Render();
}
