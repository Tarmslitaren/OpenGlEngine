#include "Mesh.h"
#include <iostream>

using namespace GLEN;
GLEN::Mesh::Mesh(std::string id, const Material & material, const VertexContent & data, DrawFrequency drawFrequency)
:m_material(material), m_vertexData(data)
{
	m_polygonMode = GL_FILL;
	Finalize(drawFrequency, id);
}
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
	RenderInternal();
}

void GLEN::Mesh::Render()
{
	m_material.Render(); //this method should only be run from here and needs to be run from here.
	RenderInternal();
}


void GLEN::Mesh::SetVerticeData(float data[], int size)
{
	SetVerticeData(data, size, m_vertexLayout);
}

void GLEN::Mesh::SetVerticeData(float data[], int size, const VertexLayout& vertexLayout)
{
	m_vertexLayout = vertexLayout;
	m_vertexData.interleavedVertices.clear();
	m_vertexData.interleavedVertices.insert(m_vertexData.interleavedVertices.begin(), &data[0], &data[size]);
}

void GLEN::Mesh::SetIndexData(unsigned int data[], int size)
{
	m_vertexData.indexes.clear();
	m_vertexData.indexes.insert(m_vertexData.indexes.begin(), &data[0], &data[size]);
}

int GLEN::Mesh::Finalize(DrawFrequency frequency, std::string id)
{
	m_frequency = frequency;
	m_id = id;

	glGenBuffers(1, &m_vertexBufferObjectHandle);

	glGenBuffers(1, &m_elementBufferObject);

	glGenVertexArrays(1, &m_vertexArrayObjectHandle);

	// 1. bind Vertex Array Object
	glBindVertexArray(m_vertexArrayObjectHandle);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectHandle);

	if (m_vertexData.interleavedVertices.size() > 0)
	{
		InitInterleaved();
	}
	else{
		InitNonInterleaved();
	}

	//3 copy index buffer
	if (m_vertexData.indexes.size() > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertexData.indexes.size() * sizeof(float), &m_vertexData.indexes[0], frequency);
	}

	return m_vertexArrayObjectHandle;
}

void GLEN::Mesh::RenderInternal()
{
	glBindVertexArray(m_vertexArrayObjectHandle);

	glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);
	if (m_vertexData.indexes.size() == 0) {
		if (m_vertexData.interleavedVertices.size() > 0)
		{
			glDrawArrays(GL_TRIANGLES, 0, m_vertexData.interleavedVertices.size() / 3); //todo: generalize: other modes than GL_TRIANGLES
			//todo: the devide by 3 here should be a bug if the verice size is bigger than three: should devide by stride instead
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, m_vertexData.positions.size() / 3);
		}
	}
	else
	{
		glDrawElements(GL_TRIANGLES, m_vertexData.indexes.size(), GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); //need this to reset?
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //set back to fill
}

void GLEN::Mesh::InitInterleaved()
{
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.interleavedVertices.size() * sizeof(float), &m_vertexData.interleavedVertices[0], m_frequency);

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
}

void GLEN::Mesh::InitNonInterleaved()
{
	const int sizeOfFloat = sizeof(float);

	int size = m_vertexData.positions.size() + m_vertexData.normals.size() + m_vertexData.texCoords.size() + m_vertexData.colors.size();
	glBufferData(GL_ARRAY_BUFFER, size * sizeOfFloat, NULL, m_frequency);


	int offset = 0;
	int dataSize = m_vertexData.positions.size() * sizeOfFloat;
	
	glBufferSubData(GL_ARRAY_BUFFER, offset, dataSize, &m_vertexData.positions[0]);
	offset = dataSize;
	int attributeId = 0;

	glVertexAttribPointer(attributeId, 3, GL_FLOAT, GL_FALSE, 3 * sizeOfFloat, 0);

	glEnableVertexAttribArray(attributeId);
	if (m_vertexData.normals.size() > 0)
	{
		int dataSize = m_vertexData.normals.size() * sizeOfFloat;
		glBufferSubData(GL_ARRAY_BUFFER, offset, dataSize, &m_vertexData.normals[0]);
		
		attributeId++;
		glVertexAttribPointer(attributeId, 3, GL_FLOAT, GL_FALSE, 3 * sizeOfFloat, (void*)offset);
		glEnableVertexAttribArray(attributeId);
		offset += dataSize;
	}
	if (m_vertexData.texCoords.size() > 0)
	{
		int dataSize = m_vertexData.texCoords.size() * sizeOfFloat;
		glBufferSubData(GL_ARRAY_BUFFER, offset, dataSize, &m_vertexData.texCoords[0]);
	
		attributeId++;
		glVertexAttribPointer(attributeId, 2, GL_FLOAT, GL_FALSE, 2 * sizeOfFloat, (void*)offset);
		glEnableVertexAttribArray(attributeId);
		offset += dataSize;
	}
	if (m_vertexData.colors.size() > 0)
	{
		int dataSize = m_vertexData.colors.size() * sizeOfFloat;
		glBufferSubData(GL_ARRAY_BUFFER, offset, dataSize, &m_vertexData.colors[0]);
		attributeId++;
		glVertexAttribPointer(attributeId, 3, GL_FLOAT, GL_FALSE, 3 * sizeOfFloat, (void*)offset);
		glEnableVertexAttribArray(attributeId); //todo: is this here or in render? or shader?
		offset += dataSize;
	}


}
