#pragma once
#include "CU_Matrix.h"
#include "Camera.h"
namespace GLEN
{
	class Scene;
	class ShaderProgram;
	class Camera;
	class Mesh;
	class ShadowMap
	{
	public:
		ShadowMap();
		~ShadowMap();
		void Render(Scene* scene);
	private:
		unsigned int m_depthMapFrameBufferObject;
		unsigned int m_depthMapTexture;
		int m_depthTextureResolution = 2048;
		ShaderProgram* m_shader;
		ShaderProgram* m_shaderAlpha;
		CU::Matrix44f m_lightProjection;
		Camera m_LightPerspective;

		bool m_debugMode = true;
		ShaderProgram* m_debugShader;

		const int m_shadowMapBinding = 10; //todo: this is arbitrary, what if a mesh has moe than 9 textures? it will be oveerwritten by the material.
		Mesh* m_debugQuad;
	};
}

