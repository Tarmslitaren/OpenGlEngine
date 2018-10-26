#pragma once
#include <vector>
#include "Model.h"
#include <string>
#include "Material.h"
#include "CU_Vector.h"
namespace GLEN
{
	class MeshContainer
	{
	public:
		MeshContainer();
		~MeshContainer();
		int CreateMesh(std::string id, float* verticeData, int dataSize, VertexLayout vertexLayout, const Material& material, unsigned int* indexData = nullptr, int indexSize = 0, DrawFrequency drawFrequency = GLEN::STATIC_DRAW);
		int CreateMesh(std::string id, const VertexContent& data, const Material& material, DrawFrequency drawFrequency = GLEN::STATIC_DRAW);
		int CreateBox(std::string id, CU::Vector3f dimensions, const Material& material, DrawFrequency drawFrequency = GLEN::STATIC_DRAW);
		int CreateQuad(std::string id, CU::Vector2f dimensions, const Material& material, DrawFrequency drawFrequency = GLEN::STATIC_DRAW);
		Mesh* GetMesh(int id);
	private:
		std::vector<Mesh*> m_meshes;
	};
}

