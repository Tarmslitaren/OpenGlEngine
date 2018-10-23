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
