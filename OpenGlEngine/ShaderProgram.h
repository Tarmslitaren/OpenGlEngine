#pragma once
#include "enums.h"
namespace GLEN
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
		ShaderProgram(const char* vertexPath, const char* fragmentPath);
		~ShaderProgram();
		bool AddVertexShader(const char* source);
		bool AddFragmentShader(const char* source);
		int Finalize(); //returns the handle
		int GetHandle() { return m_shaderProgramHandle; }
		void use();
		// utility uniform functions
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
	private:
		bool AddShader(const char* path, int& handle, ShaderType shaderType);
		int m_vertexShaderHandle;
		int m_fragmentShaderHandle;
		int m_shaderProgramHandle;
	};
}

