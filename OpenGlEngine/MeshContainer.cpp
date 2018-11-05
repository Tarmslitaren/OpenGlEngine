#include "MeshContainer.h"
#include "Mesh.h"

using namespace GLEN;
MeshContainer::MeshContainer()
{
}


MeshContainer::~MeshContainer()
{
}

int GLEN::MeshContainer::CreateMesh(std::string id, const VertexContent & data, const Material & material, VertexLayout layout, DrawFrequency drawFrequency)
{
	GLEN::Mesh* mesh = new GLEN::Mesh(id, material, data, drawFrequency);
	m_meshes.push_back(mesh);
	return mesh->GetHandle();
}

int GLEN::MeshContainer::CreateMesh(std::string id, const VertexContent & data, const Material & material, DrawFrequency drawFrequency)
{
	GLEN::Mesh* mesh = new GLEN::Mesh(id, material, data, drawFrequency);
	m_meshes.push_back(mesh);
	return mesh->GetHandle();
}

int GLEN::MeshContainer::CreateBox(std::string id, CU::Vector3f dimensions, const Material & material, DrawFrequency drawFrequency)
{

	const CU::Vector3f dim = dimensions * 0.5f;
	VertexContent content;
	content.positions = {
		-dim.x, -dim.y, -dim.z,
		 dim.x, -dim.y, -dim.z,
		 dim.x,  dim.y, -dim.z,
		 dim.x,  dim.y, -dim.z,
		-dim.x,  dim.y, -dim.z,
		-dim.x, -dim.y, -dim.z,

		-dim.x, -dim.y,  dim.z,
		 dim.x, -dim.y,  dim.z,
		 dim.x,  dim.y,  dim.z,
		 dim.x,  dim.y,  dim.z,
		-dim.x,  dim.y,  dim.z,
		-dim.x, -dim.y,  dim.z,

		-dim.x,  dim.y,  dim.z,
		-dim.x,  dim.y, -dim.z,
		-dim.x, -dim.y, -dim.z,
		-dim.x, -dim.y, -dim.z,
		-dim.x, -dim.y,  dim.z,
		-dim.x,  dim.y,  dim.z,

		 dim.x,  dim.y,  dim.z,
		 dim.x,  dim.y, -dim.z,
		 dim.x, -dim.y, -dim.z,
		 dim.x, -dim.y, -dim.z,
		 dim.x, -dim.y,  dim.z,
		 dim.x,  dim.y,  dim.z,

		-dim.x, -dim.y, -dim.z,
		 dim.x, -dim.y, -dim.z,
		 dim.x, -dim.y,  dim.z,
		 dim.x, -dim.y,  dim.z,
		-dim.x, -dim.y,  dim.z,
		-dim.x, -dim.y, -dim.z,

		-dim.x,  dim.y, -dim.z,
		 dim.x,  dim.y, -dim.z,
		 dim.x,  dim.y,  dim.z,
		 dim.x,  dim.y,  dim.z,
		-dim.x,  dim.y,  dim.z,
		-dim.x,  dim.y, -dim.z
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

	int meshId = CreateMesh(id, content, material, drawFrequency);
	return meshId;
}

int GLEN::MeshContainer::CreateQuad(std::string id, CU::Vector3f dimensions, const Material & material, DrawFrequency drawFrequency)
{
	const CU::Vector3f dim = dimensions * 0.5f;
	VertexContent content;
	// a plane
	content.positions = {
		 dim.x,  dim.y, dim.z,
		 dim.x, -dim.y, dim.z,
		-dim.x, -dim.y, dim.z,
		-dim.x,  dim.y, dim.z, 
	};

	content.normals = {
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	content.texCoords = {
		 1.0f, 1.0f,   // top right
		 1.0f, 0.0f,   // bottom right
		 0.0f, 0.0f,   // bottom left
		 0.0f, 1.0f    // top left 
	};
	content.indexes = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	int meshId = CreateMesh(id, content, material, drawFrequency);
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
