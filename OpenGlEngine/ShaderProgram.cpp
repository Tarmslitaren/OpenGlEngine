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
	m_geometryShaderHandle = -1;
}


GLEN::ShaderProgram::ShaderProgram(std::string id, std::string vertexPath, std::string fragmentPath, std::string geometryPath)
{
	m_id = id;
	ShaderProgram::ShaderProgram();

	std::string vertexSource = ReadFromFile(vertexPath);
	std::string fragmentSource = ReadFromFile(fragmentPath);
	AddVertexShader(vertexSource);
	AddFragmentShader(fragmentSource);
	if (geometryPath.size() > 0) 
	{
		std::string geometrySource = ReadFromFile(geometryPath);
		AddGeometryShader(geometrySource);
	}

	Finalize();

	//basically  all shaders need the view and projection matrices
	Engine::GetInstance()->GetShaderInput().AddUniformBufferBinding("Matrices", m_shaderProgramHandle);

}

ShaderProgram::~ShaderProgram()
{
}

bool GLEN::ShaderProgram::AddVertexShader(std::string source)
{

// source for GLSL compiler
// you can prepare this array at runtime to support multiple shaders with different attributes
	std::string header = "#version 330 core\n"
		"#define VERTEX_LAYOUT_POSITION " + std::to_string((int)VERTEX_LAYOUT_POSITION) + "\n"
		"#define VERTEX_LAYOUT_TEXCOORDS " + std::to_string((int)VERTEX_LAYOUT_TEXCOORDS) + "\n"
		"#define VERTEX_LAYOUT_NORMALS " + std::to_string((int)VERTEX_LAYOUT_NORMALS) + "\n"
		"#define VERTEX_LAYOUT_COLOR " + std::to_string((int)VERTEX_LAYOUT_COLOR) + "\n"
		"#define VERTEX_LAYOUT_INSTANCE_MATRIX " + std::to_string((int)VERTEX_LAYOUT_INSTANCE_MATRIX) + "\n"
		"//"; //to comment out the #version 330 core line in the actual shader
	
	std::string res = header + source;

	m_vertexShaderHandle = glCreateShader(GLEN::VERTEX_SHADER);
	const GLchar* result = res.c_str();
	glShaderSource(m_vertexShaderHandle, 1, &result, NULL);
	glCompileShader(m_vertexShaderHandle);

	//check for compile error
	int  success;
	char infoLog[512];
	glGetShaderiv(m_vertexShaderHandle, GL_COMPILE_STATUS, &success);
	//std::cout << glGetError() << std::endl;
	if (!success)
	{
		glGetShaderInfoLog(m_vertexShaderHandle, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

bool GLEN::ShaderProgram::AddFragmentShader(std::string source)
{
	return AddShader(source, m_fragmentShaderHandle, GLEN::FRAGMENT_SHADER);
}

bool GLEN::ShaderProgram::AddGeometryShader(std::string source)
{
	return AddShader(source, m_geometryShaderHandle, GLEN::GEOMETRY_SHADER);
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
	if (m_geometryShaderHandle > 0)
	{
		glAttachShader(m_shaderProgramHandle, m_geometryShaderHandle);
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

std::string GLEN::ShaderProgram::ReadFromFile(std::string path)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string shaderCode;
	std::ifstream shaderFile;
	// ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open file
		shaderFile.open(path);
		std::stringstream shaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handler
		shaderFile.close();
		// convert stream into string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << path << std::endl;
	}
	return shaderCode;
	//todo: use FI_File instead
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

bool GLEN::ShaderProgram::AddShader(std::string source, int& handle, ShaderType shaderType)
{
	handle = glCreateShader(shaderType);

	const char * cSource = source.c_str();
	glShaderSource(handle, 1, &cSource, NULL);
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
