#pragma once
#include "ShaderProgram.h"
#include "Mesh.h"
namespace GLEN
{
	class Scene;
	class PostProcess
	{
	public:
		PostProcess();
		~PostProcess();
		void Render(Scene* scene);
		void SetShader(std::string id);
	private:
		unsigned int m_frameBufferObject;
		unsigned int m_texture;
		unsigned int m_renderBufferObject;
		ShaderProgram* m_shader;
		Mesh m_quad;
	};
}

