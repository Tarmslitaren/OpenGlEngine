#include "ShaderProgram.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ShaderInput.h"
#include "Engine.h"
using namespace GLEN;

GLEN::ShaderProgram::ShaderProgram()
{
	m_vertexShaderHandle = -1;
	m_fragmentShaderHandle = -1;
	m_shaderProgramHandle = -1;
}


GLEN::ShaderProgram::ShaderProgram(std::string id, std::string vertexPath, std::string fragmentPath)
{
	m_id = id;
	ShaderProgram::ShaderProgram();

	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " <<std::endl;
	}

	//todo: use FI_File instead

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	AddVertexShader(vShaderCode);
	AddFragmentShader(fShaderCode);
	Finalize();

	//basically  all shaders need the view and projection matrices
	Engine::GetInstance()->GetShaderInput().AddUniformBufferBinding("Matrices", m_shaderProgramHandle);

}

ShaderProgram::~ShaderProgram()
{
}

bool GLEN::ShaderProgram::AddVertexShader(const char * source)
{
	return AddShader(source, m_vertexShaderHandle, GLEN::VERTEX_SHADER);
}

bool GLEN::ShaderProgram::AddFragmentShader(const char * source)
{
	return AddShader(source, m_fragmentShaderHandle, GLEN::FRAGMENT_SHADER);
}

int GLEN::ShaderProgram::Finalize()
{
	m_shaderProgramHandle = glCreateProgram();
	if (m_vertexShaderHandle > 0)
	{
		glAttachShader(m_shaderProgramHandle, m_vertexShaderHandle);
	}
	if (m_fragmentShaderHandle > 0)
	{
		glAttachShader(m_shaderProgramHandle, m_fragmentShaderHandle);
	}
	glLinkProgram(m_shaderProgramHandle);

	//check errors
	int success;
	char infoLog[512];
	glGetProgramiv(m_shaderProgramHandle, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProgramHandle, 512, NULL, infoLog);
		std::cout << "ERROR::SHADERPROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//we no longer need these:(maybe!?)
	glDeleteShader(m_vertexShaderHandle);
	glDeleteShader(m_fragmentShaderHandle);

	return m_shaderProgramHandle;
}

void GLEN::ShaderProgram::use()
{
	if (m_shaderProgramHandle > 0)
	{
		glUseProgram(m_shaderProgramHandle);

		//temp uniform test
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int handle = m_shaderProgramHandle;
		int vertexColorLocation = glGetUniformLocation(handle, "ourColor");
		if (vertexColorLocation == -1) {
			std::cout << "can't find uniform" << std::endl;
		}
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
	}
}

void GLEN::ShaderProgram::setBool(const std::string & name, bool value)
{
	use();
	int location = glGetUniformLocation(m_shaderProgramHandle, name.c_str());
	if (location >= 0)
	{
		glUniform1i(location, (int)value);
	}
}

void GLEN::ShaderProgram::setInt(const std::string & name, int value)
{
	use();
	int location = glGetUniformLocation(m_shaderProgramHandle, name.c_str());
	if (location >= 0)
	{
		glUniform1i(location, value);
	}
}

void GLEN::ShaderProgram::setFloat(const std::string & name, float value)
{
	use();
	int location = glGetUniformLocation(m_shaderProgramHandle, name.c_str());
	if (location >= 0)
	{
		glUniform1f(location, value);
	}
}

void GLEN::ShaderProgram::setMatrix(const std::string & name, CU::Matrix44f matrix)
{
	use();
	int location = glGetUniformLocation(m_shaderProgramHandle, name.c_str());
	if (location >= 0)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, matrix.myMatrix[0]);
	}
}

void GLEN::ShaderProgram::setVector(const std::string & name, CU::Vector3f vector)
{
	use();
	int location = glGetUniformLocation(m_shaderProgramHandle, name.c_str());
	if (location >= 0)
	{
		glUniform3f(location, vector.x, vector.y, vector.z);
	}
}

void GLEN::ShaderProgram::setVector4(const std::string & name, CU::Vector4f vector)
{
	use();
	int location = glGetUniformLocation(m_shaderProgramHandle, name.c_str());
	if (location >= 0)
	{
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}
}

bool GLEN::ShaderProgram::AddShader(const char * source, int& handle, ShaderType shaderType)
{
	handle = glCreateShader(shaderType);

	glShaderSource(handle, 1, &source, NULL);
	glCompileShader(handle);

	//check for compile error
	int  success;
	char infoLog[512];
	glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
	//std::cout << glGetError() << std::endl;
	if (!success)
	{
		glGetShaderInfoLog(handle, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}
