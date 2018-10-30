#pragma once
#include "enums.h"
#include "CU_Matrix.h"
#include <string>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
namespace GLEN
{

	enum ShaderType {
		VERTEX_SHADER = GL_VERTEX_SHADER,
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER //aka pixel shader
	};

	class ShaderProgram
	{
	public:
		ShaderProgram();
		ShaderProgram(std::string id, std::string vertexPath, std::string fragmentPath, std::string geometryShader);
		~ShaderProgram();
		int GetHandle() { return m_shaderProgramHandle; }
		std::string GetId() { return m_id; }
		void use();
		// utility uniform functions
		void setBool(const std::string &name, bool value);
		void setInt(const std::string &name, int value);
		void setFloat(const std::string &name, float value);
		void setMatrix(const std::string &name, CU::Matrix44f matrix);
		void setVector(const std::string &name, CU::Vector3f vector);
		void setVector4(const std::string &name, CU::Vector4f vector);
	private:
		bool AddShader(std::string path, int& handle, ShaderType shaderType);
		bool AddVertexShader(std::string source);
		bool AddFragmentShader(std::string source);
		bool AddGeometryShader(std::string source);
		int Finalize(); //returns the handle
		std::string ReadFromFile(std::string path);
		int m_vertexShaderHandle;
		int m_fragmentShaderHandle;
		int m_geometryShaderHandle;
		int m_shaderProgramHandle;
		std::string m_id;
	};
}

