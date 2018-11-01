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
		void SetUseMSAA(bool use) { m_msaa = use; }
	private:
		void Init();
		void InitMsaa();
		bool m_msaa = true;
		unsigned int m_frameBufferObject;
		unsigned int m_texture;
		unsigned int m_renderBufferObject;
		ShaderProgram* m_shader;
		Mesh* m_quad;

		//msaa stuff
		unsigned int m_msaaFrameBufferObject;
		unsigned int m_msaaIntermediateFrameBufferObject;
		unsigned int rbo;
		unsigned int textureColorBufferMultiSampled;
		unsigned int screenTexture;
		Mesh* m_msaaQuad;
	};
}

