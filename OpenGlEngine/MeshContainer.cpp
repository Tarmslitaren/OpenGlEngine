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

int GLEN::MeshContainer::CreateQuad(std::string id, CU::Vector2f dimensions, const Material & material, bool strech, DrawFrequency drawFrequency)
{
	float planeVertices[] = {
		// positions            // normals         // texcoords
		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,//0
		-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,//1
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,//3

		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,//1
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,//2
		 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f//3
	};
	const CU::Vector2f dim = dimensions * 0.5f;
	VertexContent content;
	// a plane
	content.positions = {
		 dim.x,  dim.y, 0,
		 dim.x, -dim.y, 0,
		-dim.x, -dim.y, 0,
		-dim.x,  dim.y, 0, 
	};


	/*
	v1        v2
	+---------+
	|         |  normal is CrossProduct((v2-v1), (v3-v1))
	|         |
	+---------+
	v3        v4
	*/

	CU::Vector3f v1v2 = CU::Vector3f{ dim.x, -dim.y, 0 } - CU::Vector3f{ dim.x, dim.y, 0 };
	CU::Vector3f v3v1 = CU::Vector3f{ -dim.x, -dim.y, 0 } - CU::Vector3f{ dim.x, -dim.y, 0 };
	CU::Vector3f normal = v1v2.Cross(v3v1).GetNormalized();


	content.normals = {
	normal.x, normal.y, normal.z,
	normal.x, normal.y, normal.z,
	normal.x, normal.y, normal.z,
	normal.x, normal.y, normal.z,
	};

	CU::Vector2f uv = dim;
	if (strech)
	{
		uv = { 1,1 };
	}

	content.texCoords = {
		 uv.x, uv.y,   // top right
		 uv.x, 0.0f,   // bottom right
		 0.0f, 0.0f,   // bottom left
		 0.0f, uv.y    // top left 
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
