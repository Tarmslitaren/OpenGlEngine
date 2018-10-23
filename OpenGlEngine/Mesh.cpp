#include "Mesh.h"
#include <iostream>

using namespace GLEN;
Mesh::Mesh(const Material& material)
:m_material(material)
{
	m_polygonMode = GL_FILL;
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObjectHandle);
	glDeleteBuffers(1, &m_vertexBufferObjectHandle);
}

void GLEN::Mesh::Render(const CU::Matrix44f& model)
{

	

	m_material.Render(model); //this method should only be run from here and needs to be run from here.

	glBindVertexArray(m_vertexArrayObjectHandle);

	glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);

	if (m_indexes.size() == 0) {
		glDrawArrays(GL_TRIANGLES, 0, m_vertices.size() / 3); //todo: generalize: other modes than GL_TRIANGLES
	}
	else
	{
		glDrawElements(GL_TRIANGLES, m_indexes.size(), GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); //need this to reset?
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //set back to fill

}

void GLEN::Mesh::AddVertice(const CU::Vector3f& vertice)
{
	m_vertices.push_back(vertice.x);
	m_vertices.push_back(vertice.y);
	m_vertices.push_back(vertice.z);
}

void GLEN::Mesh::SetVerticeData(float data[], int size)
{
	SetVerticeData(data, size, m_vertexLayout);
}

void GLEN::Mesh::SetVerticeData(float data[], int size, const VertexLayout& vertexLayout)
{
	m_vertexLayout = vertexLayout;
	m_vertices.clear();
	m_vertices.insert(m_vertices.begin(), &data[0], &data[size]);
}

void GLEN::Mesh::SetIndexData(unsigned int data[], int size)
{
	m_indexes.clear();
	m_indexes.insert(m_indexes.begin(), &data[0], &data[size]);
}

void GLEN::Mesh::AddTriangleIndexes(const CU::Vector3i indexes)
{
	m_indexes.push_back(indexes.x);
	m_indexes.push_back(indexes.y);
	m_indexes.push_back(indexes.z);
}

int GLEN::Mesh::Finalize(DrawFrequency frequency, std::string id)
{
	m_id = id;

	glGenBuffers(1, &m_vertexBufferObjectHandle);

	glGenBuffers(1, &m_elementBufferObject);

	glGenVertexArrays(1, &m_vertexArrayObjectHandle);

	// ..:: Initialization code (done once (unless your object frequently changes)) :: ..
	// 1. bind Vertex Array Object
	glBindVertexArray(m_vertexArrayObjectHandle);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectHandle);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], frequency);

	//3 copy index buffer
	if (m_indexes.size() > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexes.size() * sizeof(float), &m_indexes[0], frequency);
	}

	// 4. then set our vertex attributes pointers
	//0 is for the atrribute nr. we could query this instead of setting in the shader
	//but this needs to be run after shader is attached,
	/*int posAttributeLocation = glGetAttribLocation(m_shaderProgram.GetHandle(), "position");
	if (posAttributeLocation < 0) {
		std::cout << "can't find attribute location" << std::endl;
		posAttributeLocation = 0;
	}*/


	//todo: this can be more general
	glVertexAttribPointer(m_vertexLayout.locationAtrribute, 3, GL_FLOAT, GL_FALSE, m_vertexLayout.stride * sizeof(float), (void*)m_vertexLayout.vertexOffset);
	glEnableVertexAttribArray(m_vertexLayout.locationAtrribute);
	if (m_vertexLayout.hasColor == true)
	{
		glVertexAttribPointer(m_vertexLayout.colorAtribute, 3, GL_FLOAT, GL_FALSE, m_vertexLayout.stride * sizeof(float), (void*)(m_vertexLayout.colorOffset * sizeof(float)));
		glEnableVertexAttribArray(m_vertexLayout.colorAtribute);
	}

	if (m_vertexLayout.hasTexCoords == true)
	{
		glVertexAttribPointer(m_vertexLayout.texCoordAttribute, 3, GL_FLOAT, GL_FALSE, m_vertexLayout.stride * sizeof(float), (void*)(m_vertexLayout.texCoordOffset * sizeof(float)));
		glEnableVertexAttribArray(m_vertexLayout.texCoordAttribute);
	}
	if (m_vertexLayout.hasNormals == true)
	{
		glVertexAttribPointer(m_vertexLayout.normalsAttribute, 3, GL_FLOAT, GL_FALSE, m_vertexLayout.stride * sizeof(float), (void*)(m_vertexLayout.normalOffset * sizeof(float)));
		glEnableVertexAttribArray(m_vertexLayout.normalsAttribute);
	}

	return m_vertexArrayObjectHandle;
}
