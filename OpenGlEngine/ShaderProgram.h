#pragma once
#include "enums.h"
#include "CU_Matrix.h"
#include <string>
namespace GLEN
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
		ShaderProgram(std::string id, std::string vertexPath, std::string fragmentPath);
		~ShaderProgram();
		bool AddVertexShader(const char* source);
		bool AddFragmentShader(const char* source);
		int Finalize(); //returns the handle
		int GetHandle() { return m_shaderProgramHandle; }
		std::string GetId() { return m_id; }
		void use();
		// utility uniform functions
		void setBool(const std::string &name, bool value);
		void setInt(const std::string &name, int value);
		void setFloat(const std::string &name, float value);
		void setMatrix(const std::string &name, CU::Matrix44f matrix);
		void setVector(const std::string &name, CU::Vector3f matrix);
	private:
		bool AddShader(const char* path, int& handle, ShaderType shaderType);
		int m_vertexShaderHandle;
		int m_fragmentShaderHandle;
		int m_shaderProgramHandle;
		std::string m_id;
	};
}

