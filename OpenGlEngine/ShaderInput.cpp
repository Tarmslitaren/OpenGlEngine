#include "ShaderInput.h"
#include "glad/glad.h"
#include "Engine.h"
#include "ShaderContainer.h"
#include "ShaderProgram.h"
using namespace GLEN;

ShaderInput::ShaderInput()
{
	glGenBuffers(1, &m_Matrices);

	glBindBuffer(GL_UNIFORM_BUFFER, m_Matrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(CU::Matrix44<float>), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_Matrices, 0, 2 * sizeof(CU::Matrix44<float>));
}


ShaderInput::~ShaderInput()
{
}

void GLEN::ShaderInput::SetMatrixes(const CU::Matrix44<float> & projection, const CU::Matrix44<float> & view)
{

	//todo: make seperate method to supply only view,a s proj is not updated as often
	//proj
	glBindBuffer(GL_UNIFORM_BUFFER, m_Matrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(CU::Matrix44<float>), projection.myMatrix);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);

	//glBindBuffer(GL_UNIFORM_BUFFER, m_Matrices);

	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(CU::Matrix44<float>), sizeof(CU::Matrix44<float>), view.myMatrix);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void GLEN::ShaderInput::AddUniformBufferBinding(std::string id, int shaderHandle)
{

	int uniformBlockIndex = glGetUniformBlockIndex(shaderHandle, id.c_str());
	if (uniformBlockIndex >= 0)
		glUniformBlockBinding(shaderHandle, uniformBlockIndex, 0);
	
}

void GLEN::ShaderInput::UpdateStandardUniforms()
{
	//todo: general, not just these shaders.
	Engine::GetInstance()->GetShaderContainer().GetShaderProgram("explode")->setFloat("time", glfwGetTime());
	Engine::GetInstance()->GetShaderContainer().GetShaderProgram("reflectShader")->setVector("cameraPos", Engine::GetInstance()->GetCamera().GetPosition());
}
