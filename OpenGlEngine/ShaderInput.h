#pragma once
#include "CU_Matrix.h"
#include <string>
namespace GLEN
{;
	class ShaderInput
	{
	public:
		ShaderInput();
		~ShaderInput();
		void SetMatrixes(const CU::Matrix44<float>& projection, const CU::Matrix44<float>& view);
		void AddUniformBufferBinding(std::string id, int shaderHandle);
		void UpdateStandardUniforms();
	private:
		unsigned int m_Matrices;
	};
}

