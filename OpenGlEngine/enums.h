#pragma once
#include "CU_Vector.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
namespace GLEN
{
	struct SetupInfo
	{
		//bool myWindowedMode;
		CU::Vector2<int> m_resolution{ 800, 600 };
		//int myColorDepth;
		//int myZBufferDepth;
		//int myStencilDepth;
		//std::string mySessionName;
	};

	enum ShaderType {
		VERTEX_SHADER = GL_VERTEX_SHADER,
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER //aka pixel shader
	};

}