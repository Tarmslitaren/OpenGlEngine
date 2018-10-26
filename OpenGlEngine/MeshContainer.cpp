#include "MeshContainer.h"
#include "Mesh.h"

using namespace GLEN;
MeshContainer::MeshContainer()
{
}


MeshContainer::~MeshContainer()
{
}

int GLEN::MeshContainer::CreateMesh(std::string id, float * verticeData, int dataSize, VertexLayout vertexLayout, const Material& material, unsigned int* indexData, int indexSize, DrawFrequency drawFrequency)
{
	//todo: this
	//sanity check
	//if (GetMesh(id) != nullptr)
	//{
	//	std::cout << "trying to add mesh with same id!" << std::endl;
	//	return GetMesh(id)->GetHandle();
	//}
	GLEN::Mesh* mesh = new GLEN::Mesh(material);
	mesh->SetVerticeData(verticeData, dataSize, vertexLayout);
	if (indexData != nullptr)
	{
		mesh->SetIndexData(indexData, indexSize);
	}
	int handle = mesh->Finalize(drawFrequency, id);
	m_meshes.push_back(mesh);
	return handle;
}

int GLEN::MeshContainer::CreateMesh(std::string id, const VertexContent & data, const Material & material, DrawFrequency drawFrequency)
{
	GLEN::Mesh* mesh = new GLEN::Mesh(id, material, data, drawFrequency);
	m_meshes.push_back(mesh);
	return mesh->GetHandle();
}

int GLEN::MeshContainer::CreateBox(std::string id, CU::Vector3f dimensions, const Material & material, DrawFrequency drawFrequency)
{

	VertexContent content;
	content.positions = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};

	content.normals = {
		 // normals           // texture coords
		 0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,

		 0.0f,  0.0f, 1.0f, 
		 0.0f,  0.0f, 1.0f, 
		 0.0f,  0.0f, 1.0f, 
		 0.0f,  0.0f, 1.0f, 
		 0.0f,  0.0f, 1.0f, 
		 0.0f,  0.0f, 1.0f, 

		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,

		 1.0f,  0.0f,  0.0f,
		 1.0f,  0.0f,  0.0f,
		 1.0f,  0.0f,  0.0f,
		 1.0f,  0.0f,  0.0f,
		 1.0f,  0.0f,  0.0f,
		 1.0f,  0.0f,  0.0f,

		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,

		 0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f
	};

	content.texCoords = {
		 0.0f, 0.0f,
		 1.0f, 0.0f,
		 1.0f, 1.0f,
		 1.0f, 1.0f,
		 0.0f, 1.0f,
		 0.0f, 0.0f,

		 0.0f, 0.0f,
		 1.0f, 0.0f,
		 1.0f, 1.0f,
		 1.0f, 1.0f,
		 0.0f, 1.0f,
		 0.0f, 0.0f,

		 1.0f, 0.0f,
		 1.0f, 1.0f,
		 0.0f, 1.0f,
		 0.0f, 1.0f,
		 0.0f, 0.0f,
		 1.0f, 0.0f,

		 1.0f, 0.0f,
		 1.0f, 1.0f,
		 0.0f, 1.0f,
		 0.0f, 1.0f,
		 0.0f, 0.0f,
		 1.0f, 0.0f,

		 0.0f, 1.0f,
		 1.0f, 1.0f,
		 1.0f, 0.0f,
		 1.0f, 0.0f,
		 0.0f, 0.0f,
		 0.0f, 1.0f,

		 0.0f, 1.0f,
		 1.0f, 1.0f,
		 1.0f, 0.0f,
		 1.0f, 0.0f,
		 0.0f, 0.0f,
		 0.0f, 1.0f
	};

	/*GLEN::VertexLayout layout;
	layout.hasTexCoords = true;
	layout.hasNormals = true;
	layout.normalOffset = 3;
	layout.texCoordOffset = 6;
	layout.texCoordAttribute = 2;
	layout.stride = 8;*/

	int meshId = CreateMesh(id, content, material, drawFrequency);
	//int meshId = CreateMesh(id, cubeVerts, sizeof(cubeVerts) / sizeof(float), layout, material);
	//GLEN::Mesh* mesh = GetMesh(meshId);
	return meshId;
}

Mesh * GLEN::MeshContainer::GetMesh(int id)
{
	for (Mesh* mesh : m_meshes)
	{
		if (mesh->GetHandle() == id)
		{
			return mesh;
		}
	}
	return nullptr;
}
